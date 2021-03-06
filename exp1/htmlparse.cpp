#include <fstream>

#include "htmlparse.h"
#include "Stack.h"

htmlParse::htmlParse(int tnumber) :
	pagenumber(tnumber),
	bigtype(tnumber),
	smalltype(tnumber),
	title(tnumber),
	author(tnumber),
	posttype(tnumber),
	date(tnumber),
	context(tnumber),
	visauthor(tnumber,false),
	viscontext(tnumber,false),
	visdate(tnumber, 0),
	isgbk(tnumber,false)
{
}

htmlParse::~htmlParse()
{
}

bool htmlParse::parse(const std::string & tfilename)
{
	std::ifstream input(tfilename);
	if (!input)//check if file opened success
		return false;

	using namespace ds;
	std::string stringbuf;
	Stack<CharString> stack;
	while (std::getline(input, stringbuf)) {
		CharString line(stringbuf);
		int len = line.len();
		for (int i = 0; i < len; i++)
			if (line[i] == '<') {//find tag
				int end = i;
				for(int j=i+1;j<len;j++)
					if (line[j] == '>') {
						end = j;
						break;
					}
				CharString tag = line.substring(i, end - i + 1);
				CharString type = gettype(tag);
				if (!isSelfClose(tag)) {//check if it is self closed
					if (isClose(tag)) {
						if (!stack.empty()) {
							CharString starttype = gettype(stack.top());
							if (starttype == type)
								stack.pop();
						}
						else {
							addBadTag(tag);//it is not normal closed tag
						}
					}
					else {
						stack.push(tag);
					}
				}
				i = getinfo(line, tag, input, end + 1) - 1;//from html get info
			}
	}
	return true;
}

bool htmlParse::parseAllHtml(const std::string &prefilename)
{
	for (int i = 0; i < pagenumber; i++) {
		nowpage = i;
		if (!parse(prefilename + std::to_string(i) + ".html"))
			return false;
	}
	return true;
}

//get html type
ds::CharString htmlParse::gettype(const ds::CharString & tag)
{
	int len = tag.len(), start = 0;
	while (start < len && !isalpha(tag[start]))
		start++;
	int addlen = 1;
	while (start + addlen - 1 < len && isalpha(tag[start + addlen - 1]))
		addlen++;
	return tag.substring(start, addlen-1);
}

//get tag's args
ds::CharString htmlParse::getTagArg(const ds::CharString & tag, const ds::CharString & arg)
{
	int place = tag.indexOf(arg), len = tag.len();
	if (place == -1)
		return "";
	for (int i = place; i < len; i++) {
		if (tag[i] == '\"') {
			for (int addlen = 0; i + addlen < len; addlen++)
				if (tag[i + addlen + 1] == '\"') 
					return tag.substring(i + 1, addlen);
		}
	}
	return "";
}

bool htmlParse::isSelfClose(const ds::CharString & tag)
{
	if (gettype(tag) == TAGTYPE::meta)
		return true;
	return tag[tag.len() - 2] == '/';
}

bool htmlParse::isClose(const ds::CharString & tag)
{
	return tag[1] == '/';
}

void htmlParse::addBadTag(const ds::CharString & tag)
{
	badtags.push_back(tag);
}

int htmlParse::getinfo(
	const ds::CharString &context,
	const ds::CharString &tag,
	std::ifstream &input,
	int endplace)
{
	static bool foundauthor = false;
	
	ds::CharString type = gettype(tag);
	int len = context.len();
	if (type == TAGTYPE::div) {
		ds::CharString argclass = getTagArg(tag, "class");
		//get bigtype smalltype and title
		if (argclass == "z") {
			std::string buf;
			std::getline(input, buf);
			ds::CharString info(buf);
			int infolen = info.len(), place = 0, addlen = 0;
			for (int i = 0; i < infolen; i++)
				if (info[i] == '>') {
					place++;
					addlen = 0;
					if (place == TYPEPLACE::bigtype) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						bigtype[nowpage] = (info.substring(i + 1, addlen));
					}
					if (place == TYPEPLACE::smalltype) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						smalltype[nowpage] = (info.substring(i + 1, addlen));
					}
					if (place == TYPEPLACE::title) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						title[nowpage] = (info.substring(i + 1, addlen));
					}
				}
			return context.len() - 1;
		}
		//get posttype
		if (argclass == "ts z h1") {
			std::string buf;
			std::getline(input, buf);
			ds::CharString info(buf);
			int infolen = info.len(), place = 0, addlen = 0;
			for (int i = 0; i < infolen; i++)
				if (info[i] == '>') {
					place++;
					addlen = 0;
					if (place == TYPEPLACE::posttype) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						posttype[nowpage] = (info.substring(i + 1, addlen));
						return context.len() - 1;
					}
				}
		}
		//get author
		if (!visauthor[nowpage] && argclass == "authi") {
			const ds::CharString &info = context;
			int infolen = info.len(), place = 0, addlen = 0;
			for (int i = 0; i < infolen; i++)
				if (info[i] == '>') {
					place++;
					addlen = 0;
					if (place == TYPEPLACE::author) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						author[nowpage] = (info.substring(i + 1, addlen));
						visauthor[nowpage] = true;
						return context.len() - 1;
					}
				}
		}
		// get context
		if (!viscontext[nowpage] && argclass == "t_fsz") {
			std::string buf;
			std::getline(input, buf);
			std::getline(input, buf);
			ds::CharString info(buf);
			int infolen = info.len(), place = 0, addlen = 0;
			int testlen = 0;
			while (testlen < infolen&&info[testlen] == ' ')
				testlen++;
			if (info[testlen] != '<') {
				place++;
				isgbk[nowpage] = true;
			}
			for (int i = testlen-1; i < infolen; i++) {
				if (info[i] == '>') {
					place++;
				}
				if (place == TYPEPLACE::context) {
					addlen = 0;
					while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
						++addlen;
					htmlParse::context[nowpage] = (info.substring(i + 1, addlen));
					viscontext[nowpage] = true;
					return context.len() - 1;
				}
			}
		}
		if (visdate[nowpage] < 1 && argclass == "authi")
			visdate[nowpage] ++;
		//get date
		if (visdate[nowpage] == 1 && argclass == "authi") {
			std::string buf;
			std::getline(input, buf);
			ds::CharString info(buf);
			int infolen = info.len(), place = 0, addlen = 0;
			for (int i = 0; i < infolen; i++)
				if (info[i] == '>') {
					place++;
					addlen = 0;
					if (place == TYPEPLACE::date) {
						while (i + addlen + 1 < infolen&&info[i + addlen + 1] != '<')
							++addlen;
						date[nowpage] = (info.substring(i + 8, addlen - 7));//ignore three characters
						visdate[nowpage]++;
						return context.len() - 1;
					}
				}
		}
	}
	return endplace;
}
