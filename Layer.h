#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsItemGroup>

#include "ILong.h"
#include "SQLExcute.h"
#include "Geometry.h"

/*
 * 提供简单的图元管理功能
 * */

class ILong;
class ILONGSHARED_EXPORT Layer : public QObject
{
    Q_OBJECT
public:

    typedef struct
    {
        quint32 id;
        QPointF center;
        QString label;
        QList<QPointF> list;
        int size;
        int flags;
        QColor pen;
        QColor brush;
    } ILongInfo;
    /*
     * 新增图层
     * @name 图层名称
     * @typeList 图层数据结构
     * */
    explicit Layer(ILong * parent,QString name, QList<LayerFormat> * typeList);
    /*
     * 从数据库里加载图层,所有参数都在数据库管理表里得到
     * */
    Layer(ILong * parent, QString id, QString name, bool visible, bool selectable);
    ~Layer();
    QSqlQuery * searchInfo(QString field, QString text);
    void setViewToItem(QString itemID);
    void addGeo(Geometry::ILongDataType data);
    void addGeos(QList<Geometry::ILongDataType> * dataList);
    QList<Geometry *> *getItems();
    void updatLayer(bool * isUpdate);
    void setLabel(QString field = "ILONGNULL");
    void updateGeoPenColor(quint32 geoID, QColor c = QColor(Qt::red));
    void updateGeoBrushColor(quint32 geoID, QColor c = QColor(Qt::yellow));
    void removeGeo(QString itemID);
    /*
     * 返回图层名称
     * */
    QString getLayerName();
    /*
     * 返回图层ID,和数据库里的表关联
     * */
    QString getLayerID();
    /*
     * 设置和返回图层可视状态
     * */
    QList<LayerFormat> *getLayerHead();
    void setVisible(bool b);
    bool isVisible();
    /*
     * 设置和返回图层可选状态
     * */
    void setSelectable(bool b);
    bool isSelectable();
    QPointF getItemPosByID(QString itemID);
private:
    ILongInfo getInfo(QSqlQuery * query);
    QList<QPointF> getGisList(QString gis);
    ILong * iLong;
    QString layerLabel;
    /*
     * 保存当前图层的图元指针
     * */
    //QList<QGraphicsItem *> list;
    QString layerID;
    bool visible;
    bool selectable;
    SQLExcute * sqlExcute;
    /*
     * 保存当前图层的字段类型,只为了方便导入数据时数据转换检查
     * */
    QList <LayerFormat> headType;
    QList <Geometry *> list;

signals:
    void addGeoToScene(Geometry *);
public slots:
};

#endif // LAYER_H
