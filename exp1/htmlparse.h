#pragma once

#include <string>
#include <vector>

#include "CharString.h"
//for tag type
namespace TAGTYPE {
	static const ds::CharString meta = ds::CharString("meta");
	static const ds::CharString div = ds::CharString("div");
}
//support html parse
namespace TYPEPLACE {
	const int
		bigtype(9),
		smalltype(13),
		title(17),
		posttype(1),
		author(2),
		date(1),
		context(1);
}

class htmlParse {
	typedef std::vector<ds::CharString> container;
public:
	htmlParse(int tnumber = 0);
	~htmlParse();
	bool parse(const std::string &tfilename);
	bool parseAllHtml(const std::string &prefilename);//use it to parse all html
	std::vector<bool> isgbk;
	// containers below are final htmlparse results
	container bigtype, smalltype, title, author, context, date, posttype;

private:

	//these functions can use for tag check
	ds::CharString gettype(const ds::CharString &tag);
	ds::CharString getTagArg(const ds::CharString &tag, const ds::CharString &arg);
	inline bool isSelfClose(const ds::CharString &tag);
	inline bool isClose(const ds::CharString &tag);
	inline void addBadTag(const ds::CharString &tag);
	int getinfo(
		const ds::CharString &context,
		const ds::CharString &tag,
		std::ifstream &input,
		int endplace
	);

	//store parse-needing info
	container badtags;
	std::vector<bool> visauthor, viscontext;
	std::vector<int> visdate;

	int pagenumber;
	int nowpage;

};