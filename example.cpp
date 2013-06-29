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

    return 0;
}
