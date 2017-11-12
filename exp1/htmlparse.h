#pragma once

#include <string>
#include "myds.h"
#include <vector>

namespace TAGTYPE {
	static const ds::CharString meta = ds::CharString("meta");
	static const ds::CharString div = ds::CharString("div");
}
namespace TYPEPLACE {
	const int bigtype(9);
	const int smalltype(13);
	const int title(17);
	const int posttype(1);
	const int author(2);

}
class htmlParse {
public:
	htmlParse(int tnumber = 0);
	~htmlParse();
	bool parse(const std::string &tfilename);
	bool parseAllHtml(const std::string &prefilename);

private:
	typedef std::vector<ds::CharString> container;

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

	container badtags;
	container bigtype, smalltype, title, author, context, date, posttype;
	std::vector<bool> visauthor;

	int pagenumber;
	int nowpage;

	void debugOutput(const container& out);
};