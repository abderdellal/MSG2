#include "coordinatewidget.h"
#include <QHBoxLayout>
#include <QMessageBox>



coordinateWidget::coordinateWidget(QWidget *parent) :
    QWidget(parent)
{
    x = 0;
    y = 0;

    QHBoxLayout * layout = new QHBoxLayout();
    labelX = new QLabel("X ");
    editX = new QLineEdit();
    labelY = new QLabel("Y ");
    editY = new QLineEdit();
    QIcon iconeSelect("select.png");
    boutton = new QPushButton(iconeSelect, "Select");


    editX->setMaximumWidth(40);
    editY->setMaximumWidth(40);
    editX->setMinimumWidth(35);
    editY->setMinimumWidth(35);

    layout->addWidget(labelX);
    layout->addWidget(editX);
    layout->addWidget(labelY);
    layout->addWidget(editY);
    layout->addWidget(boutton);

    this->setLayout(layout);

    QObject::connect(boutton, SIGNAL(clicked()), this, SLOT(changeCoordinate()));
}

int coordinateWidget::setX(QString X)
{
    bool ok;
    int temp = X.toInt(&ok);
    if(ok)
    {
       x = temp - 1;
       return 0;
    }
    else
    {
        QMessageBox::question(this, "Erreur","Vérifier le Champ X");
        return 1;
    }
}

int coordinateWidget::setY(QString Y)
{
    bool ok;
    int temp = Y.toInt(&ok);
    if(ok)
    {
       y = temp - 1;
       return 0;
    }
    else
    {
        QMessageBox::question(this, "Erreur","Vérifier le Champ Y");
        return 1;
    }
}

void coordinateWidget::setXY(int X, int Y)
{
    QString s;

    x = X;
    s.setNum(x + 1);
    editX->setText(s);

    y = Y;
    s.setNum(y + 1);
    editY->setText(s);
}

int coordinateWidget::getX()
{
    return x;
}

int coordinateWidget::getY()
{
    return y;
}

void coordinateWidget::changeCoordinate()
{
    int b = 0;

    QString s;
    s = editX->text();
    b = b + setX(s);

    s = editY->text();
    b = b + setY(s);

    if(b == 0)
    {
        emit coordinateChanged(x, y);
    }
}
