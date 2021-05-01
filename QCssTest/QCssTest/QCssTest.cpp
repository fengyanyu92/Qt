#include "QCssTest.h"
#include "fontTool.h"
#include <QDirModel>
#include <QScrollBar>
#include <QTextCodec>
#include <QIcon>

QCssTest::QCssTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon(":/image/qt-logo.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->installEventFilter(this);
    initControl();
    ui.TabBtn1->click();
    nComboxNum_ = 3;
}

bool QCssTest::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this)
    {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
		if (event->type() == QEvent::MouseMove && mousePressed_)
		{
			this->move(mouseEvent->globalPos() - mousePoint_);
		}
		else if (event->type() == QEvent::MouseButtonPress && mouseEvent->button() == Qt::LeftButton)
		{
            mousePressed_ = true;
            mousePoint_ = mouseEvent->globalPos() - this->pos();
		}
		else if (event->type() == QEvent::MouseButtonRelease && mouseEvent->button() == Qt::LeftButton)
		{
            mousePressed_ = false;
		}
    }
	return QWidget::eventFilter(watched, event);
}

void QCssTest::initControl()
{
    ui.titleLabel->setText(QString::fromLocal8Bit("Qt CSS样式测试（作者：枫焱宇 博客：<a href=\"https://blog.csdn.net/weixin_52511809\">枫焱宇</a>）"));

    auto comboxView = new QListView(ui.comboBox);
    comboxView->setFocusPolicy(Qt::FocusPolicy::NoFocus);// 没法去掉虚线框，在CSS中用outline去掉
    ui.comboBox->setView(comboxView);
    ui.comboBox->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    // 按钮
    auto font = fontTool::service()->fontAt(fontTool::EFT_Icon);
    ui.addBtn->setFont(font);
    ui.addBtn->setText(QChar(0xe604));
    ui.addBtn->setToolTip(QString::fromLocal8Bit("添加下拉项"));
    ui.minBtn->setFont(font);
    ui.minBtn->setText(QChar(0xe629));
    ui.minBtn->setToolTip(QString::fromLocal8Bit("最小化"));
    ui.maxBtn->setFont(font);
    ui.maxBtn->setText(QChar(0xe60e));
    ui.maxBtn->setToolTip(QString::fromLocal8Bit("最大化"));
    ui.closeBtn->setFont(font);
    ui.closeBtn->setText(QChar(0xe61e));
    ui.closeBtn->setToolTip(QString::fromLocal8Bit("退出"));

    // 加载我的电脑
    QDirModel* model = new QDirModel(this);
    ui.treeView->setModel(model);
    ui.tableView->setModel(model);
    ui.listView->setModel(model);

	ui.treeView->header()->setOffsetToLastSection();
	ui.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.treeView->setFocusPolicy(Qt::FocusPolicy::NoFocus);// 去掉选中时的虚线框
    ui.tableView->setSelectionModel(ui.treeView->selectionModel());
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableView->verticalHeader()->hide();
	ui.tableView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui.listView->setSelectionModel(ui.treeView->selectionModel());
	ui.listView->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    ui.treeView->verticalScrollBar()->setContentsMargins(0, 30, 0, 0);

    // text
	QFile file("./text.txt");
	if (file.open(QFile::ReadOnly | QFile::Text)) {
		QByteArray ba = file.readAll();
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		QString str = codec->toUnicode(ba);
		ui.textEdit->setText(str);
		ui.plainTextEdit->setPlainText(str);
		file.close();
	}

    initConnect();
}

void QCssTest::initConnect()
{
	connect(ui.addBtn, SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
	connect(ui.minBtn, SIGNAL(clicked()), this, SLOT(onMinBtnClicked()));
	connect(ui.maxBtn, SIGNAL(clicked()), this, SLOT(onMaxBtnClicked()));
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
	connect(ui.TabBtn1, SIGNAL(clicked()), this, SLOT(onLeftBtn1Clicked()));
	connect(ui.TabBtn2, SIGNAL(clicked()), this, SLOT(onLeftBtn2Clicked()));
    connect(ui.horizontalSlider, &QSlider::valueChanged, ui.progressBar, [&](int value) {
        ui.progressBar->setValue(value);
        });
}

Q_SLOT void QCssTest::onAddBtnClicked()
{
    ui.comboBox->addItem(QString::fromLocal8Bit("下拉数据%1").arg(++nComboxNum_));
}

Q_SLOT void QCssTest::onMinBtnClicked()
{
    showMinimized();
}

Q_SLOT void QCssTest::onMaxBtnClicked()
{
    if (this->isMaximized())
    {
        showNormal();
        ui.maxBtn->setText(QChar(0xe60e));
        ui.maxBtn->setToolTip(QString::fromLocal8Bit("最大化"));
    }
    else
    {
        showMaximized();
        ui.maxBtn->setText(QChar(0xe613));
        ui.maxBtn->setToolTip(QString::fromLocal8Bit("还原"));
    }
}

Q_SLOT void QCssTest::onCloseBtnClicked()
{
    this->close();
}

Q_SLOT void QCssTest::onLeftBtn1Clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
	ui.TabBtn1->setChecked(true);
	ui.TabBtn2->setChecked(false);
}

Q_SLOT void QCssTest::onLeftBtn2Clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
	ui.TabBtn1->setChecked(false);
	ui.TabBtn2->setChecked(true);
}
