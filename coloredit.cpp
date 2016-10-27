#include "coloredit.h"
#include "ui_coloredit.h"
#include <QColorDialog>

ColorEdit::ColorEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorEdit)
{
    ui->setupUi(this);
    setColor(Qt::white);
}

ColorEdit::~ColorEdit()
{
    delete ui;
}

void ColorEdit::setColor(const QColor &color)
{
    _color = color;

    QPalette palette = ui->lineEdit->palette();
    palette.setColor(ui->lineEdit->backgroundRole(), color);
    ui->lineEdit->setPalette(palette);
}

void ColorEdit::on_toolButton_clicked()
{
    QColor color = QColorDialog::getColor(_color, this);
    if (color.isValid()) {
        setColor(color);
        emit colorEdited(color);
    }
}
