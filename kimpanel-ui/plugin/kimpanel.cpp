/*
    SPDX-FileCopyrightText: 2020 Weng Xuetian <wengxt@gmail.com>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#include "kimpanel.h"
#include <QDebug>
Kimpanel::Kimpanel(QObject *parent)
    : QObject(parent)
    , m_panelAgent(new PanelAgent(this))
{
    connect(m_panelAgent, &PanelAgent::updateAux, this, &Kimpanel::updateAux);
    connect(m_panelAgent, &PanelAgent::updatePreeditText, this, &Kimpanel::updatePreeditText);
    connect(m_panelAgent, &PanelAgent::updatePreeditCaret, this, &Kimpanel::updatePreeditCaret);
    connect(m_panelAgent, &PanelAgent::updateLookupTable, this, &Kimpanel::updateLookupTable);
    connect(m_panelAgent, &PanelAgent::updateSpotLocation, this, &Kimpanel::updateSpotLocation);
    connect(m_panelAgent, &PanelAgent::updateSpotRect, this, &Kimpanel::updateSpotRect);
    connect(m_panelAgent, &PanelAgent::showAux, this, &Kimpanel::showAux);
    connect(m_panelAgent, &PanelAgent::showPreedit, this, &Kimpanel::showPreedit);
    connect(m_panelAgent, &PanelAgent::showLookupTable, this, &Kimpanel::showLookupTable);
    connect(m_panelAgent, &PanelAgent::updateLookupTableCursor, this, &Kimpanel::updateLookupTableCursor);
    connect(m_panelAgent, &PanelAgent::updateLookupTableFull, this, &Kimpanel::updateLookupTableFull);

    connect(m_panelAgent, &PanelAgent::updateProperty, this, &Kimpanel::updateProperty);
    connect(m_panelAgent, &PanelAgent::registerProperties, this, &Kimpanel::registerProperties);
    connect(m_panelAgent, &PanelAgent::execMenu, this, &Kimpanel::execMenu);
    connect(m_panelAgent, &PanelAgent::execDialog, this, &Kimpanel::execDialog);
}

Kimpanel::~Kimpanel()
{

}

void Kimpanel::updateAux(const QString &text, const QList<TextAttribute> &attrList)
{
    qDebug() << "updateAux" << text;
    Q_UNUSED(attrList);
    if (m_auxText != text) {
        m_auxText = text;
        emit auxTextChanged();
    }
}

void Kimpanel::updatePreeditText(const QString &text, const QList<TextAttribute> &attrList)
{
    qDebug() << "updatePreeditText" << text;
    Q_UNUSED(attrList);
    if (m_preeditText != text) {
        m_preeditText = text;
        emit preeditTextChanged();
    }
}

void Kimpanel::updatePreeditCaret(int pos)
{
    qDebug() << "updatePreeditCaret" << pos;
    if (m_caretPos != pos) {
        m_caretPos = pos;
        emit preeditTextChanged();
    }
}

void Kimpanel::updateLookupTable(const KimpanelLookupTable &lookupTable)
{
    m_labels.clear();
    m_texts.clear();
    for (const KimpanelLookupTable::Entry &entry : lookupTable.entries) {
        m_labels << entry.label;
        m_texts << entry.text;
    }
    m_hasPrev = lookupTable.has_prev;
    m_hasNext = lookupTable.has_next;
    emit lookupTableChanged();
}

void Kimpanel::updateSpotLocation(int x, int y)
{
    //qDebug() << "updateSpotLocation" << x << "  " << y;
    updateSpotRect(x, y, 0, 0);
}

void Kimpanel::updateSpotRect(int x, int y, int w, int h)
{
    //qDebug() << "updateSpotRect" << x << "  " << y  << "  " << w << "  " << h;
    m_spotRect = QRect(x, y, w, h);
    emit spotRectChanged(x, y, w, h);
}

void Kimpanel::showAux(bool visible)
{
    //qDebug() << "showAux" << visible;
    if (m_auxVisible != visible) {
        m_auxVisible = visible;
        emit auxTextChanged();
    }
}

void Kimpanel::showPreedit(bool visible)
{
    //qDebug() << "showPreedit" << visible;
    if (m_preeditVisible != visible) {
        m_preeditVisible = visible;
        emit preeditTextChanged();
    }
}

void Kimpanel::showLookupTable(bool visible)
{
    //qDebug() << "showLookupTable" << visible;
    if (m_lookupTableVisible != visible) {
        m_lookupTableVisible = visible;
        emit lookupTableChanged();
    }
}

void Kimpanel::updateLookupTableCursor(int cursor)
{
    //qDebug() << "updateLookupTableCursor" << cursor;
    if (m_lookupTableCursor != cursor) {
        m_lookupTableCursor = cursor;
        emit lookupTableChanged();
    }
}

void Kimpanel::updateLookupTableFull(const KimpanelLookupTable &lookupTable, int cursor, int layout)
{
    m_labels.clear();
    m_texts.clear();
    for (const KimpanelLookupTable::Entry &entry : lookupTable.entries) {
        m_labels << entry.label;
        m_texts << entry.text;
    }
    m_hasPrev = lookupTable.has_prev;
    m_hasNext = lookupTable.has_next;
    m_lookupTableCursor = cursor;
    m_lookupTableLayout = layout;
    emit lookupTableChanged();
}

void Kimpanel::updateProperty(const KimpanelProperty &property)
{
    //qDebug() << "updateProperty: " << property.key << "  " << property.label << "  " << property.icon << "  " << property.hint << "  " << property.tip << "  "  ;
    emit propertiesChanged(property.key, property.label);
    for (auto &prop : m_props) {
        if (prop.toMap()[QStringLiteral("key")] == property.key) {
            prop = property.toMap();
            //emit propertiesChanged(property.key, property.label);
            break;
        }
    }
}

void Kimpanel::registerProperties(const QList<KimpanelProperty> &props)
{
    //qDebug() << "registerProperties: " << props;
    m_props.clear();
    for (const auto &prop : props) {
        m_props << prop.toMap();
        qDebug() << "registerProperties: " << prop.key << "  " << prop.label << "  " << prop.icon << "  " << prop.hint << "  " << prop.tip << "  "  ;
        emit propertiesChanged(prop.key, prop.label);
    }
}

void Kimpanel::execMenu(const QList<KimpanelProperty> &props)
{
    QVariantList menuProps;
    for (const auto &prop : props) {
        menuProps << prop.toMap();
    }
    emit menuTriggered(menuProps);
}

void Kimpanel::execDialog(const KimpanelProperty &property)
{
    qDebug() << "execDialog: " << property.key << "  " << property.label << "  " << property.icon << "  " << property.hint << "  " << property.tip << "  "  ;
}

void Kimpanel::configure()
{
    m_panelAgent->configure();
}

void Kimpanel::exit()
{
    m_panelAgent->exit();
}

void Kimpanel::lookupTablePageDown()
{
    m_panelAgent->lookupTablePageDown();
}

void Kimpanel::lookupTablePageUp()
{
    m_panelAgent->lookupTablePageUp();
}

void Kimpanel::movePreeditCaret(int position)
{
    m_panelAgent->movePreeditCaret(position);
}

void Kimpanel::reloadConfig()
{
    m_panelAgent->reloadConfig();
}

void Kimpanel::selectCandidate(int candidate)
{
    m_panelAgent->selectCandidate(candidate);
}

void Kimpanel::triggerProperty(const QString &key)
{
    m_panelAgent->triggerProperty(key);
}













