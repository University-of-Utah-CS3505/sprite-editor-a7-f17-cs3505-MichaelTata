#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <vector>

class Model : public QObject
{
    Q_OBJECT
private:
    // frames will contain all of the frames, or images, of the current project.
    std::vector<QImage> frames;
    // undoes and redoes hold the different states of the current image
    // and allow for them to be undone or redone.
    std::vector<QImage> undoes;
    std::vector<QImage> redoes;
    // The view will show the current image and it is the only image
    // that can be worked on at a time.
    QImage& currentImage;
    /* The current tool directs how the image will be manipulated.
     * An encoding for the tools would work best to distinguish them
     * from each other.
     * The encoding is the following:
     * 0 = pen
     * 1 = erase
     * 2 = select
     * 3 = fill
     * 4 = line
     * 5 = rectangle
     * 6 = oval
     * Add more tools as needed.
     */
    int currentTool;
    QColor currentColor;
    QPainter painter;
    QColorDialog colorPicker;
    // This file dialog will handle creating a new project, saving, loading, and exporting a gif.
    QFileDialog fileDia;
public:
    explicit Model(QObject *parent = 0);

signals:

public slots:
};

#endif // MODEL_H
