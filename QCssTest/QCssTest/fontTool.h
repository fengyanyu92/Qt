#pragma once
#include <QFont>
#include <algorithm>
#include <memory>
#include <QFontDatabase>
#include <map>

using std::map;

class fontTool;
typedef std::shared_ptr<fontTool> fontToolPtr;


/*仅适用于非系统字体库*/
class fontTool
{
public:
	enum EFontType
	{
		EFT_Title = 0,

		EFT_ChildTitle,
		
		EFT_Label,
		
		EFT_Button,
		
		EFT_List,
		
		EFT_Table,

		EFT_Icon,

		EFT_Other1,
		EFT_Other2,
		EFT_Other3
	};
public:
	fontTool() {}
	static fontToolPtr newPtr(){ return std::make_shared<fontTool>(); }

private:
	map<EFontType, QFont> _mapFont;

public:
	static fontToolPtr service()
	{
		static fontToolPtr toolObj = nullptr;
		if (!toolObj)
			toolObj = fontTool::newPtr();
		return toolObj;
	}

	bool addThirdpartyFontLib(const QString& fontPath, EFontType type);

	QFont fontAt(EFontType type);

	bool setFontStyle(EFontType type, bool bold, int pixSize, bool bItalic);
};