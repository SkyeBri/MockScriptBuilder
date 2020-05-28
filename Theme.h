#ifndef THEME_H
#define THEME_H

#include <QColor>

struct Theme
{
    // Default to Dark Theme
    QColor ContainerBackground       {QColor("#333333")};
    QColor ContainerHandleBackground {QColor("#555555")};
    QColor SectionBackground         {QColor("#555555")};
    QColor SectionBorder             {QColor("#555555")};
    QColor SectionTitleBackground    {QColor("#555555")};
    QColor SectionTitleBorder        {QColor("#333333")};
    QColor SelectedTabHighlight      {QColor("#444444")};
    QColor SelectedTabBackground     {QColor("#333333")};
    QColor SectionContentBackground  {QColor("#333333")};
    QColor SectionContentBorder      {QColor("#333333")};
    QColor MainColor0                {QColor("#555555")};
    QColor MainColor1                {QColor("#333333")};
    QColor TextColor                 {QColor("white")};
    QColor DisabledTextColor         {QColor("#888888")};

    Theme () {}

    Theme(QColor containerBG, QColor containerHandleBG, QColor sectionBG, QColor sectionBorder, QColor titleBG,
          QColor titleBorder, QColor tabHighlight,      QColor tabBG,     QColor contentBG,     QColor contentBorder,
          QColor main0,       QColor main1,             QColor text,      QColor disabledText) :
        ContainerBackground(containerBG), ContainerHandleBackground(containerHandleBG), SectionBackground(sectionBG),
        SectionBorder(sectionBorder), SectionTitleBackground(titleBG), SectionTitleBorder(titleBorder),
        SelectedTabHighlight(tabHighlight), SelectedTabBackground(tabBG), SectionContentBackground(contentBG),
        SectionContentBorder(contentBorder), MainColor0(main0), MainColor1(main1), TextColor(text),
        DisabledTextColor(disabledText)
    {}
};

const Theme DarkTheme;

#endif // THEME_H
