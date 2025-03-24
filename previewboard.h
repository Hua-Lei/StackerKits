#ifndef PREVIEWBOARD_H
#define PREVIEWBOARD_H

#include <QWidget>

class PreviewBoard : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewBoard(int previewNum, QWidget *parent = nullptr);
private:
    int previewNum;
signals:
};

#endif // PREVIEWBOARD_H
