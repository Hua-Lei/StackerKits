#ifndef ASPECTWIDGET_H
#define ASPECTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QResizeEvent>

class AspectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AspectWidget(QHBoxLayout* layout, double aspectRatio, QWidget *parent = nullptr)
        : QWidget(parent), aspectRatio(aspectRatio){setLayout(layout);};
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    double aspectRatio;
signals:
};

#endif // ASPECTWIDGET_H
