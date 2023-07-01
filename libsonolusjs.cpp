#include"../../main.cpp"
#include<bits/stdc++.h>
using namespace std;

void copyFolder(string src, string dst) {
    MKDIR(dst);
    for (auto& p: filesystem::directory_iterator(src)) {
        if (filesystem::is_directory(p)) copyFolder(p.path().string(), dst + "/" + p.path().filename().string());
        else filesystem::copy_file(p.path().string(), dst + "/" + p.path().filename().string());
    }
}

void initCustomEngine(char** argv) {
    string root_dir = string(argv[2]);
    copyFolder("./plugins/libsonolusjs/source", root_dir);
    system(("cd \"" + root_dir + "\" && npm install").c_str());
}

bool fileExist(string path) {
    ifstream fin(path.c_str());
    return fin.is_open();
}
string uploadFile(string path) {
    ifstream fin(path.c_str());
    fin.seekg(0, ios::end);
    int len = fin.tellg();
    fin.seekg(0, ios::beg);
    char* filePointerBeg = new char[len];
    fin.read(filePointerBeg, len);
    unsigned char* fileSha1 = sha1(filePointerBeg, len);
    stringstream buffer;
    for (int i = 0; i < 20; i++)
        buffer << hex << setw(2) << setfill('0') << int(fileSha1[i]);
    ofstream fout(("./data/" + buffer.str()).c_str());
    fout.write(filePointerBeg, len); fout.close();
    free(filePointerBeg); free(fileSha1);
    return buffer.str();
}

void initBuild(string path) {
    int res = system(("cd \"" + path + "\" && npm run build").c_str());
    if (res) exit(3);

    preload();
    string package_json = readFile((path + "/package.json").c_str());
    Json::Value arr; json_decode(package_json, arr);
    SkinItem skin; BackgroundItem background; EffectItem effect; ParticleItem particle;
    auto tmp = skinList("name = \"" + arr["skin"].asString() + "\"");
    if (tmp.items.size() == 0) writeLog(LOG_LEVEL_ERROR, "Failed to find skin \"" + arr["skin"].asString() + "\""), exit(0);
    skin = tmp.items[0];
    auto tmp2 = backgroundList("name = \"" + arr["background"].asString() + "\"");
    if (tmp2.items.size() == 0) writeLog(LOG_LEVEL_ERROR, "Failed to find background \"" + arr["background"].asString() + "\""), exit(0);
    background = tmp2.items[0];
    auto tmp3 = effectList("name = \"" + arr["effect"].asString() + "\"");
    if (tmp3.items.size() == 0) writeLog(LOG_LEVEL_ERROR, "Failed to find effect \"" + arr["effect"].asString() + "\""), exit(0);
    effect = tmp3.items[0];
    auto tmp4 = particleList("name = \"" + arr["particle"].asString() + "\"");
    if (tmp4.items.size() == 0) writeLog(LOG_LEVEL_ERROR, "Failed to find particle \"" + arr["particle"].asString() + "\""), exit(0);
    particle = tmp4.items[0];

    string engineData = uploadFile((path + "/dist/EngineData").c_str());
    string engineConfiguration = uploadFile((path + "/dist/EngineConfiguration").c_str());
    string engineThumbnail = fileExist((path + "/dist/thumbnail.jpg").c_str()) ?
        uploadFile((path + "/dist/thumbnail.jpg").c_str()) : uploadFile((path + "/dist/thumbnail.png").c_str()); 

    engineCreate(EngineItem(-1, arr["name"].asString(), arr["title"].asString(), arr["subtitle"].asString(), arr["author"].asString(), 
        skin, background, effect, particle, SRL<EngineThumbnail>(engineThumbnail, ""), SRL<EngineData>(engineData, ""), 
        SRL<EngineConfiguration>(engineConfiguration, ""), SRL<EngineRom>("", "")), true);
}

class PluginSonolusjs: public SonolusServerPlugin {
    public:
    
    string onPluginName() const {
        return "Sonolus.js Plugin";
    }
    string onPluginDescription() const {
        return "TypeScript based Developer Toolkit for Sonolus";
    }
    string onPluginVersion() const {
        return "1.0.0";
    }
    string onPluginPlatformVersion() const {
        return sonolus_server_version;
    }
    string onPluginAuthor() const {
        return "Burrito(Extended by LittleYang0531)";
    }
    string onPluginLicense() const {
        return "MIT";
    }
    string onPluginWebsite() const {
        return "https://github.com/Sonolus/sonolus.js";
    }
    vector<string> onPluginHelp(char** argv) const {
        return {
            "Sonolus.js init: " + string(argv[0]) + " initjs [name]",
            "Sonolus.js build: " + string(argv[0]) + " buildjs [name]"
        };
    }
    void onPluginRunner(int argc, char** argv) const {
        if (string(argv[1]) == "initjs") {
            if (argc < 3) return;
            initCustomEngine(argv);
            exit(0);
        } else if (string(argv[1]) == "buildjs") {
            if (argc < 3) return;
            initBuild(argv[2]);
            serverRunner(argc, argv);
            exit(0);
        } return;
    }
    void onPluginRouter(int argc, char** argv, application *app) const {
        
    }
};

PLUMA_INHERIT_PROVIDER(PluginSonolusjs, SonolusServerPlugin);

PLUMA_CONNECTOR
bool pluma_connect(pluma::Host& host) {
    host.add( new PluginSonolusjsProvider() );
    return true;
}