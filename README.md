# **qt-json**
## *a simple JSON class for Qt* 
                                   
---
          
### 1. INTRODUCTION ###

The **qt-json** class is a simple class for parsing [JSON][js] data into a [QVariant][var] 
hierarchies. Now, we can also reverse the process and serialize
QVariant hierarchies into valid JSON data.

**NOTE:** As of Qt5 this class has become obsolete, because Qt5 already has [a native JSON object class][qt5]. Even so, as Qt4 will still be around for a little longer, this project is to be maintained for legacy support.

---

### 2. HOW TO USE ###
#### 2.1. Parsing JSON ####

The parser is really easy to use. Let's say we have the following 
QString of JSON data:

```js
{
"encoding" : "UTF-8",
"plug-ins" : [
    "python",
    "c++",
    "ruby"
],
"indent" : {
    "length" : 3,
    "use_space" : true
    }
}
```

We would first call the parse-method:

```cpp
//Say that we're using the QtJson namespace
using namespace QtJson;
bool ok;
//json is a QString containing the JSON data
QVariantMap result = Json::parse(json, ok).toMap();

if(!ok) {
qFatal("An error occurred during parsing");
exit(1);
```

Assuming the parsing process completed without errors, we would then
go through the hierarchy:

```cpp
qDebug() << "encoding:" << result["encoding"].toString();
qDebug() << "plugins:";

foreach(QVariant plugin, result["plug-ins"].toList()) {
    qDebug() << "\t-" << plugin.toString();
}

QVariantMap nestedMap = result["indent"].toMap();
qDebug() << "length:" << nestedMap["length"].toInt();
qDebug() << "use_space:" << nestedMap["use_space"].toBool();
```

The previous code would print out the following:

    encoding: "UTF-8"
    plugins:
      - "python"
      - "c++"
      - "ruby"
    length: 3
    use_space: true

---

#### 2.2. Serializing JSON ####
To write JSON data from Qt object is as simple as creating and assigning data to a [QVariantMap][varmap]:

```cpp
QVariantMap map;
map["name"] = "Name";
map["age"] = 22;

QByteArray data = Json::serialize(map);
```

The byte array 'data' contains valid JSON data:

```js
{
    name: "Luis Gustavo",
    age: 22
}
```

After creating the QVariantMap, you can create a [QVariantList][varlist] and append the QVariantMaps. 

```cpp    
QVariantMap friend1, friend2, friend3;
friend1["id"] = 1;
friend1["name"] = "MackenzieHamphrey";
friend2["id"] = 2;
friend2["name"] = "MelanieMolligan";
friend3["id"] = 3;
friend3["name"] = "SydneyCalhoun";

QVariantList friendsList;
friendsList.append(friend1);
friendsList.append(friend2);
friendsList.append(friend3);

QVariantMap friendObject;
friendObject["friends"] = friendList
```

This way you create a nested structure:

```js
{
    "friends": [
        {
            "id": 1,
            "name": "MackenzieHamphrey"
        },
        {
            "id": 2,
            "name": "MelanieMolligan"
        },
        {
            "id": 3,
            "name": "SydneyCalhoun"
        }
    ]
}
```

If you continue this process recursively, you nest more levels into the JSON structure.

If you want to see a more complete example, you can check out [this question](http://stackoverflow.com/questions/17039190/extract-data-from-csv-with-regex-and-convert-it-to-json "qt-json in SO") in StackOverflow.

---

### 3. CONTRIBUTING ###

The code is available to download at GitHub. Contribute if you dare! Fork it and pull requests for validation.


[js]: http://www.json.org/ "JSON Standard specification"
[var]: http://qt-project.org/doc/qt-4.8/qvariant.html "QVariant class reference"
[qt5]: http://qt-project.org/doc/qt-5.0/qtcore/qjsonobject.html "Qt5 QJsonObject class reference"
[varmap]: http://qt-project.org/doc/qt-4.8/qvariant.html#QVariantMap-typedef "Qt4 QVariantMap class reference"
[varlist]: http://qt-project.org/doc/qt-4.8/qvariant.html#QVariantList-typedef "Qt4 QVariantList class reference"