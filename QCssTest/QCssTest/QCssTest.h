#pragma once

#include <QtWidgets/QWidget>
#include "ui_QCssTest.h"

class QCssTest : public QWidget
{
    Q_OBJECT

public:
    QCssTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::QCssTestClass ui;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	

private:
    void initControl();

    void initConnect();

    Q_SLOT void onAddBtnClicked();
    Q_SLOT void onMinBtnClicked();
    Q_SLOT void onMaxBtnClicked();
    Q_SLOT void onCloseBtnClicked();
    Q_SLOT void onLeftBtn1Clicked();
    Q_SLOT void onLeftBtn2Clicked();

private:
	bool mousePressed_;
	QPoint mousePoint_;

    int nComboxNum_;
};
