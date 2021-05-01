#include "fontTool.h"
#include <assert.h>

bool fontTool::addThirdpartyFontLib(const QString& fontPath, EFontType type)
{
	int fontId = QFontDatabase::addApplicationFont(fontPath);
	if (fontId < 0)
		return false;
	QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont fontObj = QFont(fontName);
	if (type == EFT_Title)
	{
		fontObj.setPointSize(18);
		fontObj.setBold(true);
	}
	else
		fontObj.setPointSize(14);
	if (_mapFont.find(type) == _mapFont.end())
		_mapFont.insert(map<EFontType, QFont>::value_type(type, fontObj));
	else
		assert(false);
	return true;
}

QFont fontTool::fontAt(EFontType type)
{
	if (_mapFont.find(type) != _mapFont.end())
		return _mapFont.at(type);
	else
		return QFont();
}

bool fontTool::setFontStyle(EFontType type, bool bold, int pixSize, bool bItalic)
{
	if (_mapFont.find(type) == _mapFont.end())
		return false;
	_mapFont.at(type).setBold(bold);
	_mapFont.at(type).setPointSize(pixSize);
	_mapFont.at(type).setItalic(bItalic);
	return true;
}
