#include "tab_bar.h"

using namespace UI;

TabBar::TabBar(QWidget* parent)
    :   QLabel(parent)
        ,m_Tabs(this)
        ,m_AddButton(this)
{
    initializeData();
}

void
TabBar::initializeData()
{
    m_Tabs.setObjectName("tabbar_tabs");
    m_Tabs.setTabsClosable(true);
//    m_Tabs.setIconSize(QSize(27, 27));

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_Tabs.setMinimumHeight(15);

    // TODO: fix this
    m_AddButton.setFlat(true);

    m_AddButton.setObjectName("tabbar_add_button");

    mainLayout->addWidget(&m_Tabs, 0, Qt::AlignBottom);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(&m_AddButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // connect signals
    connect(&m_AddButton, SIGNAL(released()), SLOT(onAddTab()));
}

void
TabBar::onAddTab()
{
    int tabAdded = m_Tabs.addTab("");
    QUuid tabId = QUuid::createUuid();

    m_Tabs.setCurrentIndex(tabAdded);
    m_Tabs.setTabData(tabAdded, tabId);
    emit newTab(tabId);
}
