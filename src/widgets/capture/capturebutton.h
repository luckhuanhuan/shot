// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <QPushButton>
#include <QMap>
#include <QVector>

class QWidget;
class QPropertyAnimation;
class CaptureTool;

class CaptureButton : public QPushButton {
    Q_OBJECT

public:
    // Don't forget to add the new types to CaptureButton::iterableButtonTypes
    // in the .cpp and the order value in the private array buttonTypeOrder
    enum ButtonType {
        TYPE_MOVESELECTION,   //截图
        TYPE_SELECTIONINDICATOR,   //录屏
        TYPE_RECTANGLE,  //矩形
        TYPE_CIRCLE,     //圆形
        TYPE_DRAWER,     //直线
        TYPE_ARROW,      //箭头
        TYPE_PENCIL,     //画笔
        TYPE_MARKER,     //mark 标记
        TYPE_TEXT,       //字体
        TYPE_BLUR,       //模糊
        TYPE_UNDO,       //撤回
        TYPE_OPEN_APP,   //选项
        TYPE_EXIT,       //退出
        TYPE_COPY,       //复制
        TYPE_SAVE,       //保存
        TYPE_PIN,        //顶针
    };

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    Q_ENUMS(ButtonType)
#else
    Q_ENUM(ButtonType)
#endif

    CaptureButton() = delete;
    explicit CaptureButton(const ButtonType, QWidget *parent = nullptr);

    static QString globalStyleSheet();
    static QVector<CaptureButton::ButtonType> getIterableButtonTypes();
    static int getPriorityByButton(CaptureButton::ButtonType);

    QString name() const;
    QString description() const;
    QIcon icon() const;
    QString styleSheet() const;
    CaptureTool* tool() const;

    void setColor(const QColor &c);
    void animatedShow();

protected:
    virtual void mousePressEvent(QMouseEvent *);
    static QVector<ButtonType> iterableButtonTypes;

    CaptureTool *m_tool;

signals:
    void pressedButton(CaptureButton *);

private:
    CaptureButton(QWidget *parent = nullptr);
    ButtonType m_buttonType;

    QPropertyAnimation *m_emergeAnimation;

    static QColor m_mainColor;

    void initButton();
    void updateIcon();
};
