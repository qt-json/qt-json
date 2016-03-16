#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "json.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

QString readFile(const QString &filename) {
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        return QString();
    } else {
        QTextStream in(&f);
        return in.readAll();
    }
}

void printResult(const JsonObject &result) {
    qDebug() << "encoding:" << result["encoding"].toString();
    qDebug() << "plugins:";

    JsonArray plugins = result["plug-ins"].toList();
    foreach(QVariant plugin, plugins) {
        qDebug() << "  -" << plugin.toString();
    }

    JsonObject indent = result["indent"].toMap();
    qDebug() << "length:" << indent["length"].toInt();
    qDebug() << "use_space:" << indent["use_space"].toBool();
}

void printJson(const JsonObject &result) {
    qDebug() << QtJson::serialize(result);
}

void testClone()
{
    bool ok;

    // use an example form http://json.org/example.html
    QString json = readFile("complex.json");
    if (json.isEmpty())
        qFatal("Could not read JSON file!");

    JsonObject a = QtJson::parse(json, ok).toMap();
    printJson(a);

    JsonObject b = QtJson::clone(a).toMap();
    printJson(b);

    if (QtJson::serializeStr(a) != QtJson::serializeStr(b))
        qFatal("An error occured while cloning");
}

void testObj()
{
    QtJson::Object json;

    // compile-only test, needs to be improved

    json["int"] = 0;

    json["str"]["a"] = QString("StringA");
    json["str"]["b"] = QString("StringB");
    json["str"]["c"] = QString("StringC");

    json["obj"]["QVariant"] = QVariant();
    json["obj"]["QVariantMap"] = QVariantMap();
    json["obj"]["QVariantHash"] = QVariantHash();

    qDebug() << "QtJson::Object [1]" << QtJson::serialize(json);

    json.remove("obj");

    qDebug() << "QtJson::Object [2]" << QtJson::serialize(json);
}

int main(int argc, char **argv) {
    QString json = readFile("example.json");
    if (json.isEmpty()) {
        qFatal("Could not read JSON file!");
        return 1;
    }

    bool ok;
    JsonObject result = QtJson::parse(json, ok).toMap();
    if (!ok) {
        qFatal("An error occurred during parsing");
        return 1;
    }

    printResult(result);

    // Add extra object to result which contains an array of keywords and a ratio.
    JsonArray keywords = JsonArray() << "json" << "qt" << "parser";
    JsonObject extra;
    extra["ratio"] = 3.35;
    extra["keywords"] = keywords;
    result["extra"] = extra;

    printJson(result);

    testClone();
    testObj();

    return 0;
}
