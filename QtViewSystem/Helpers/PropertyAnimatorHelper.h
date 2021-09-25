#ifndef PROPERTYANIMATORHELPER_H
#define PROPERTYANIMATORHELPER_H

#include <Tools/TypeSafeKeyValuePropertyAnimators.h>

class PropertyAnimatorHelper {
public:
    KeyValuePropertyAnimator_QBitArray *getQBitArrayAnimator(QBitArray *valuePointer)
    {
        return new KeyValuePropertyAnimator_QBitArray([valuePointer] (const QBitArray & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_bool *getBoolAnimator(bool *valuePointer)
    {
        return new KeyValuePropertyAnimator_bool([valuePointer] (const bool & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QByteArray *getQByteArrayAnimator(QByteArray *valuePointer)
    {
        return new KeyValuePropertyAnimator_QByteArray([valuePointer] (const QByteArray & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QChar *getQCharAnimator(QChar *valuePointer)
    {
        return new KeyValuePropertyAnimator_QChar([valuePointer] (const QChar & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QDate *getQDateAnimator(QDate *valuePointer)
    {
        return new KeyValuePropertyAnimator_QDate([valuePointer] (const QDate & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QDateTime *getQDateTimeAnimator(QDateTime *valuePointer)
    {
        return new KeyValuePropertyAnimator_QDateTime([valuePointer] (const QDateTime & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_double *getDoubleAnimator(double *valuePointer)
    {
        return new PropertyAnimator_double([valuePointer] (const double & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_double *getDoubleKeyValueAnimator(double *valuePointer)
    {
        return new KeyValuePropertyAnimator_double([valuePointer] (const double & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QEasingCurve *getQEasingCurveAnimator(QEasingCurve *valuePointer)
    {
        return new KeyValuePropertyAnimator_QEasingCurve([valuePointer] (const QEasingCurve & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_float *getFloatAnimator(float *valuePointer)
    {
        return new PropertyAnimator_float([valuePointer] (const float & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_float *getFloatKeyValueAnimator(float *valuePointer)
    {
        return new KeyValuePropertyAnimator_float([valuePointer] (const float & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QHash__QString_QVariant *getQHash__QString_QVariant__Animator(QHash<QString, QVariant> *valuePointer)
    {
        return new KeyValuePropertyAnimator_QHash__QString_QVariant([valuePointer] (const QHash<QString, QVariant> & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_int *getIntAnimator(int *valuePointer)
    {
        return new PropertyAnimator_int([valuePointer] (const int & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_int *getIntKeyValueAnimator(int *valuePointer)
    {
        return new KeyValuePropertyAnimator_int([valuePointer] (const int & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QJsonArray *getQJsonArrayAnimator(QJsonArray *valuePointer)
    {
        return new KeyValuePropertyAnimator_QJsonArray([valuePointer] (const QJsonArray & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QJsonDocument *getQJsonDocumentAnimator(QJsonDocument *valuePointer)
    {
        return new KeyValuePropertyAnimator_QJsonDocument([valuePointer] (const QJsonDocument & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QJsonObject *getQJsonObjectAnimator(QJsonObject *valuePointer)
    {
        return new KeyValuePropertyAnimator_QJsonObject([valuePointer] (const QJsonObject & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QJsonValue *getQJsonValueAnimator(QJsonValue *valuePointer)
    {
        return new KeyValuePropertyAnimator_QJsonValue([valuePointer] (const QJsonValue & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QLine *getQLineAnimator(QLine *valuePointer)
    {
        return new KeyValuePropertyAnimator_QLine([valuePointer] (const QLine & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QLineF *getQLineFAnimator(QLineF *valuePointer)
    {
        return new KeyValuePropertyAnimator_QLineF([valuePointer] (const QLineF & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QList__QVariant *getQList__QVariant__Animator(QList<QVariant> *valuePointer)
    {
        return new KeyValuePropertyAnimator_QList__QVariant([valuePointer] (const QList<QVariant> & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QLocale *getQLocaleAnimator(QLocale *valuePointer)
    {
        return new KeyValuePropertyAnimator_QLocale([valuePointer] (const QLocale & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_qlonglong *getQLongLongAnimator(qlonglong *valuePointer)
    {
        return new PropertyAnimator_qlonglong([valuePointer] (const qlonglong & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_qlonglong *getQLongLongKeyValueAnimator(qlonglong *valuePointer)
    {
        return new KeyValuePropertyAnimator_qlonglong([valuePointer] (const qlonglong & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QMap__QString_QVariant *getQMap__QString_QVariant__Animator(QMap<QString, QVariant> *valuePointer)
    {
        return new KeyValuePropertyAnimator_QMap__QString_QVariant([valuePointer] (const QMap<QString, QVariant> & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QModelIndex *getQModelIndexAnimator(QModelIndex *valuePointer)
    {
        return new KeyValuePropertyAnimator_QModelIndex([valuePointer] (const QModelIndex & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QPersistentModelIndex *getQPersistentModelIndexAnimator(QPersistentModelIndex *valuePointer)
    {
        return new KeyValuePropertyAnimator_QPersistentModelIndex([valuePointer] (const QPersistentModelIndex & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QPoint *getQPointAnimator(QPoint *valuePointer)
    {
        return new KeyValuePropertyAnimator_QPoint([valuePointer] (const QPoint & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QPointF *getQPointFAnimator(QPointF *valuePointer)
    {
        return new KeyValuePropertyAnimator_QPointF([valuePointer] (const QPointF & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_qreal *getQRealAnimator(qreal *valuePointer)
    {
        return new PropertyAnimator_qreal([valuePointer] (const qreal & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_qreal *getQRealKeyValueAnimator(qreal *valuePointer)
    {
        return new KeyValuePropertyAnimator_qreal([valuePointer] (const qreal & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QRect *getQRectAnimator(QRect *valuePointer)
    {
        return new KeyValuePropertyAnimator_QRect([valuePointer] (const QRect & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QRectF *getQRectFAnimator(QRectF *valuePointer)
    {
        return new KeyValuePropertyAnimator_QRectF([valuePointer] (const QRectF & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QRegularExpression *getQRegularExpressionAnimator(QRegularExpression *valuePointer)
    {
        return new KeyValuePropertyAnimator_QRegularExpression([valuePointer] (const QRegularExpression & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QSize *getQSizeAnimator(QSize *valuePointer)
    {
        return new KeyValuePropertyAnimator_QSize([valuePointer] (const QSize & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QSizeF *getQSizeFAnimator(QSizeF *valuePointer)
    {
        return new KeyValuePropertyAnimator_QSizeF([valuePointer] (const QSizeF & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QString *getQStringAnimator(QString *valuePointer)
    {
        return new KeyValuePropertyAnimator_QString([valuePointer] (const QString & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QStringList *getQStringListAnimator(QStringList *valuePointer)
    {
        return new KeyValuePropertyAnimator_QStringList([valuePointer] (const QStringList & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QTime *getQTimeAnimator(QTime *valuePointer)
    {
        return new KeyValuePropertyAnimator_QTime([valuePointer] (const QTime & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_uint *getUIntAnimator(uint *valuePointer)
    {
        return new PropertyAnimator_uint([valuePointer] (const uint & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_uint *getUIntKeyValueAnimator(uint *valuePointer)
    {
        return new KeyValuePropertyAnimator_uint([valuePointer] (const uint & argument) {
            valuePointer[0] = argument;
        });
    }

    PropertyAnimator_qulonglong *getQULongLongAnimator(qulonglong *valuePointer)
    {
        return new PropertyAnimator_qulonglong([valuePointer] (const qulonglong & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_qulonglong *getQULongLongKeyValueAnimator(qulonglong *valuePointer)
    {
        return new KeyValuePropertyAnimator_qulonglong([valuePointer] (const qulonglong & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QUrl *getQUrlAnimator(QUrl *valuePointer)
    {
        return new KeyValuePropertyAnimator_QUrl([valuePointer] (const QUrl & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QUuid *getQUuidAnimator(QUuid *valuePointer)
    {
        return new KeyValuePropertyAnimator_QUuid([valuePointer] (const QUuid & argument) {
            valuePointer[0] = argument;
        });
    }

    KeyValuePropertyAnimator_QBitArray *getQBitArrayAnimator(std::function<void (const QBitArray &)> f)
    {
        return new KeyValuePropertyAnimator_QBitArray([f] (const QBitArray & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_bool *getBoolAnimator(std::function<void (const bool &)> f)
    {
        return new KeyValuePropertyAnimator_bool([f] (const bool & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QByteArray *getQByteArrayAnimator(std::function<void (const QByteArray &)> f)
    {
        return new KeyValuePropertyAnimator_QByteArray([f] (const QByteArray & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QChar *getQCharAnimator(std::function<void (const QChar &)> f)
    {
        return new KeyValuePropertyAnimator_QChar([f] (const QChar & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QDate *getQDateAnimator(std::function<void (const QDate &)> f)
    {
        return new KeyValuePropertyAnimator_QDate([f] (const QDate & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QDateTime *getQDateTimeAnimator(std::function<void (const QDateTime &)> f)
    {
        return new KeyValuePropertyAnimator_QDateTime([f] (const QDateTime & argument) {
            f(argument);
        });
    }

    PropertyAnimator_double *getDoubleAnimator(std::function<void (const double &)> f)
    {
        return new PropertyAnimator_double([f] (const double & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_double *getDoubleKeyValueAnimator(std::function<void (const double &)> f)
    {
        return new KeyValuePropertyAnimator_double([f] (const double & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QEasingCurve *getQEasingCurveAnimator(std::function<void (const QEasingCurve &)> f)
    {
        return new KeyValuePropertyAnimator_QEasingCurve([f] (const QEasingCurve & argument) {
            f(argument);
        });
    }

    PropertyAnimator_float *getFloatAnimator(std::function<void (const float &)> f)
    {
        return new PropertyAnimator_float([f] (const float & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_float *getFloatKeyValueAnimator(std::function<void (const float &)> f)
    {
        return new KeyValuePropertyAnimator_float([f] (const float & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QHash__QString_QVariant *getQHash__QString_QVariant__Animator(std::function<void (const QHash<QString, QVariant> &)> f)
    {
        return new KeyValuePropertyAnimator_QHash__QString_QVariant([f] (const QHash<QString, QVariant> & argument) {
            f(argument);
        });
    }

    PropertyAnimator_int *getIntAnimator(std::function<void (const int &)> f)
    {
        return new PropertyAnimator_int([f] (const int & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_int *getIntKeyValueAnimator(std::function<void (const int &)> f)
    {
        return new KeyValuePropertyAnimator_int([f] (const int & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QJsonArray *getQJsonArrayAnimator(std::function<void (const QJsonArray &)> f)
    {
        return new KeyValuePropertyAnimator_QJsonArray([f] (const QJsonArray & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QJsonDocument *getQJsonDocumentAnimator(std::function<void (const QJsonDocument &)> f)
    {
        return new KeyValuePropertyAnimator_QJsonDocument([f] (const QJsonDocument & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QJsonObject *getQJsonObjectAnimator(std::function<void (const QJsonObject &)> f)
    {
        return new KeyValuePropertyAnimator_QJsonObject([f] (const QJsonObject & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QJsonValue *getQJsonValueAnimator(std::function<void (const QJsonValue &)> f)
    {
        return new KeyValuePropertyAnimator_QJsonValue([f] (const QJsonValue & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QLine *getQLineAnimator(std::function<void (const QLine &)> f)
    {
        return new KeyValuePropertyAnimator_QLine([f] (const QLine & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QLineF *getQLineFAnimator(std::function<void (const QLineF &)> f)
    {
        return new KeyValuePropertyAnimator_QLineF([f] (const QLineF & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QList__QVariant *getQList__QVariant__Animator(std::function<void (const QList<QVariant> &)> f)
    {
        return new KeyValuePropertyAnimator_QList__QVariant([f] (const QList<QVariant> & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QLocale *getQLocaleAnimator(std::function<void (const QLocale &)> f)
    {
        return new KeyValuePropertyAnimator_QLocale([f] (const QLocale & argument) {
            f(argument);
        });
    }

    PropertyAnimator_qlonglong *getQLongLongAnimator(std::function<void (const qlonglong &)> f)
    {
        return new PropertyAnimator_qlonglong([f] (const qlonglong & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_qlonglong *getQLongLongKeyValueAnimator(std::function<void (const qlonglong &)> f)
    {
        return new KeyValuePropertyAnimator_qlonglong([f] (const qlonglong & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QMap__QString_QVariant *getQMap__QString_QVariant__Animator(std::function<void (const QMap<QString, QVariant> &)> f)
    {
        return new KeyValuePropertyAnimator_QMap__QString_QVariant([f] (const QMap<QString, QVariant> & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QModelIndex *getQModelIndexAnimator(std::function<void (const QModelIndex &)> f)
    {
        return new KeyValuePropertyAnimator_QModelIndex([f] (const QModelIndex & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QPersistentModelIndex *getQPersistentModelIndexAnimator(std::function<void (const QPersistentModelIndex &)> f)
    {
        return new KeyValuePropertyAnimator_QPersistentModelIndex([f] (const QPersistentModelIndex & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QPoint *getQPointAnimator(std::function<void (const QPoint &)> f)
    {
        return new KeyValuePropertyAnimator_QPoint([f] (const QPoint & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QPointF *getQPointFAnimator(std::function<void (const QPointF &)> f)
    {
        return new KeyValuePropertyAnimator_QPointF([f] (const QPointF & argument) {
            f(argument);
        });
    }

    PropertyAnimator_qreal *getQRealAnimator(std::function<void (const qreal &)> f)
    {
        return new PropertyAnimator_qreal([f] (const qreal & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_qreal *getQRealKeyValueAnimator(std::function<void (const qreal &)> f)
    {
        return new KeyValuePropertyAnimator_qreal([f] (const qreal & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QRect *getQRectAnimator(std::function<void (const QRect &)> f)
    {
        return new KeyValuePropertyAnimator_QRect([f] (const QRect & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QRectF *getQRectFAnimator(std::function<void (const QRectF &)> f)
    {
        return new KeyValuePropertyAnimator_QRectF([f] (const QRectF & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QRegularExpression *getQRegularExpressionAnimator(std::function<void (const QRegularExpression &)> f)
    {
        return new KeyValuePropertyAnimator_QRegularExpression([f] (const QRegularExpression & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QSize *getQSizeAnimator(std::function<void (const QSize &)> f)
    {
        return new KeyValuePropertyAnimator_QSize([f] (const QSize & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QSizeF *getQSizeFAnimator(std::function<void (const QSizeF &)> f)
    {
        return new KeyValuePropertyAnimator_QSizeF([f] (const QSizeF & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QString *getQStringAnimator(std::function<void (const QString &)> f)
    {
        return new KeyValuePropertyAnimator_QString([f] (const QString & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QStringList *getQStringListAnimator(std::function<void (const QStringList &)> f)
    {
        return new KeyValuePropertyAnimator_QStringList([f] (const QStringList & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QTime *getQTimeAnimator(std::function<void (const QTime &)> f)
    {
        return new KeyValuePropertyAnimator_QTime([f] (const QTime & argument) {
            f(argument);
        });
    }

    PropertyAnimator_uint *getUIntAnimator(std::function<void (const uint &)> f)
    {
        return new PropertyAnimator_uint([f] (const uint & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_uint *getUIntKeyValueAnimator(std::function<void (const uint &)> f)
    {
        return new KeyValuePropertyAnimator_uint([f] (const uint & argument) {
            f(argument);
        });
    }

    PropertyAnimator_qulonglong *getQULongLongAnimator(std::function<void (const qulonglong &)> f)
    {
        return new PropertyAnimator_qulonglong([f] (const qulonglong & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_qulonglong *getQULongLongKeyValueAnimator(std::function<void (const qulonglong &)> f)
    {
        return new KeyValuePropertyAnimator_qulonglong([f] (const qulonglong & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QUrl *getQUrlAnimator(std::function<void (const QUrl &)> f)
    {
        return new KeyValuePropertyAnimator_QUrl([f] (const QUrl & argument) {
            f(argument);
        });
    }

    KeyValuePropertyAnimator_QUuid *getQUuidAnimator(std::function<void (const QUuid &)> f)
    {
        return new KeyValuePropertyAnimator_QUuid([f] (const QUuid & argument) {
            f(argument);
        });
    }
};

#endif // PROPERTYANIMATORHELPER_H
