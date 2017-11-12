#include "htmlparse.h"
#include "myds.h"
#include <fstream>
#include <iostream>

htmlParse::htmlParse(int tnumber) :pagenumber(tnumber)
{
}

htmlParse::~htmlParse()
{
	for (int i = 0; i < author.size(); i++) {
		int len = author[i].len();
		for (int j = 0; j < len; j++)
			putchar(author[i][j]);
		putchar('\n');
	}
}

bool htmlParse::parse(const std::string & tfilename)
{
	std::ifstream input(tfilename);
	if (!input)
		return false;

	using namespace ds;
	std::string stringbuf;
	Stack<CharString> stack;
	while (getline(input, stringbuf)) {
		CharString line(stringbuf);
		int len = line.len();
		for (int i = 0; i < len; i++)
			if (line[i] == '<') {
				int end = i;
				for(int j=i+1;j<len;j++)
					if (line[j] == '>') {
						end = j;
						break;
					}
				CharString tag = line.substring(i, end - i + 1);
				CharString type = gettype(tag);
				if (!isSelfClose(tag)) {
					if (isClose(tag)) {
						if (!stack.empty()) {
							CharString starttype = gettype(stack.top());
							if (starttype == type)
								stack.pop();
						}
						else {
							addBadTag(tag);
						}
					}
					else {
						stack.push(tag);
					}
				}
				i = getinfo(line, tag, end + 1) - 1;
			}
	}
	return true;
}

bool htmlParse::parseAllHtml()
{
	std::string filename("buffer\\page");
	for (int i = 0; i < 100; i++)
		if (!parse(filename + std::to_string(i) + ".html"))
			return false;
	return true;
}

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
	int endplace)
{
	static bool foundauthor = false;
	
	ds::CharString type = gettype(tag);
	int len = context.len();
	if (type == TAGTYPE::title) {
		int addlen = 0;
		while (endplace + addlen < len&&context[endplace + addlen] != '<')
			addlen++;
		author.push_back(context.substring(endplace, addlen));
		return endplace + addlen;
	}
	return endplace;
}
