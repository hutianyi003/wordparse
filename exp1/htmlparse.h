#pragma once

#include <string>
#include "myds.h"
#include <vector>

namespace TAGTYPE {
	static const ds::CharString title = ds::CharString("title");
	static const ds::CharString meta = ds::CharString("meta");
}
class htmlParse {
public:
	htmlParse(int tnumber = 0);
	~htmlParse();
	bool parse(const std::string &tfilename);
	bool parseAllHtml();

private:
	typedef std::vector<ds::CharString> container;

	ds::CharString gettype(const ds::CharString &tag);
	inline bool isSelfClose(const ds::CharString &tag);
	inline bool isClose(const ds::CharString &tag);
	inline void addBadTag(const ds::CharString &tag);
	int getinfo(
		const ds::CharString &context,
		const ds::CharString &tag,
		int endplace
	);

	container badtags;
	container wholetype, detailtype, title, author, context, date, posttype;

	int pagenumber;
};