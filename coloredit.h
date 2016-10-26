#ifndef COLOREDIT_H
#define COLOREDIT_H

#include <QWidget>
#include <QColor>

namespace Ui {
class ColorEdit;
}

class ColorEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ColorEdit(QWidget *parent = 0);
    ~ColorEdit();

    QColor color() const
        { return _color; }
    void setColor(const QColor &color);

private slots:
    void on_toolButton_clicked();

private:
    Ui::ColorEdit *ui;
    QColor _color;
};

#endif // COLOREDIT_H
