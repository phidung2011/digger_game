//
//  DataManager.cpp
//  gamebase
//
//  Created by Phi Dzung on 4/14/15.
//
//

#include "DataManager.h"
#include "GameConfig.h"
#include "NativeUtils.h"
#include "PlayGameConstants.h"
USING_NS_CC;

using namespace rapidjson;

DataManager* DataManager::_instance = NULL;

DataManager* DataManager::getInstance() {
    if (!_instance)
    {
        _instance = new DataManager();
    }
	return _instance;
}

DataManager::DataManager() {
    
    
    loadGameSetting();

    CCLOG("------%s", FileUtils::getInstance()->getWritablePath().c_str());
	_totalStar = 0;
}
DataManager::~DataManager() {

}

bool DataManager::writeToJsonFile(std::string filePath,
		rapidjson::Document &document) {
//    // to Serialize to JSON String
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	document.Accept(writer);
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
//    Data data;

//    data.fastSet((unsigned char*)sb.GetString(), sb.GetSize());
    
    FileUtils::getInstance()->writeStringToFile(sb.GetString(), fullPath);
    
//	FILE *fwrite = fopen(filePath.c_str(), "w");
//	if (!fwrite) {
//		return false;
//	}
//	fprintf(fwrite, "%s", sb.GetString());
//	fclose(fwrite);

	document.Parse<0>(sb.GetString());

	return true;
}

rapidjson::Document DataManager::loadMapData(int land) {
	std::string dataPath = StringUtils::format("Maps/map_data_%d.json", land);
	std::string fullpath = "";
	ssize_t filesize;
	char* data;
	std::string content;
	fullpath = FileUtils::getInstance()->fullPathForFilename(dataPath);
	data = (char*) FileUtils::getInstance()->getFileData(fullpath.c_str(), "r",
			&filesize);
	content.append(data);
	content = content.substr(0, filesize);
	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());
	return doc;
}

rapidjson::Document DataManager::loadLevelPositionData(int land) {
	std::string dataPath = StringUtils::format("data/map_level_%d.json", land);
	std::string fullpath = "";
	ssize_t filesize;
	char* data;
	std::string content;
	fullpath = FileUtils::getInstance()->fullPathForFilename(dataPath);
	data = (char*) FileUtils::getInstance()->getFileData(fullpath.c_str(), "r",
			&filesize);
	content.append(data);
	content = content.substr(0, filesize);
	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());
	return doc;
}

void DataManager::loadStar() {
	
	std::string content = NativeUtils::getDataString(USER_DATA);

	Document::AllocatorType& allocator = _dataStar.GetAllocator();

	if (content.length() > 3) {
		_dataStar.Parse<0>(content.c_str());
	} else {

		_dataStar.SetObject();
		_dataStar.AddMember(StringRef("level_0_0"), 0, allocator);
        
        _dataStar.AddMember(StringRef("level_1_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_2_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_3_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_4_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_5_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_6_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_7_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_8_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_9_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_10_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_11_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_12_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_13_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_14_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_15_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_16_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_17_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_18_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_19_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_20_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_21_1"), 1, allocator);
        _dataStar.AddMember(StringRef("level_22_1"), 1, allocator);
//
//        _dataStar.AddMember(StringRef("level_1_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_2_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_3_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_4_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_5_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_6_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_7_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_8_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_9_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_10_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_11_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_12_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_13_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_14_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_15_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_16_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_17_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_18_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_19_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_20_2"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_21_2"), 1, allocator);
//        
//        _dataStar.AddMember(StringRef("level_1_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_2_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_3_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_4_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_5_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_6_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_7_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_8_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_9_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_10_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_11_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_12_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_13_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_14_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_15_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_16_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_17_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_18_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_19_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_20_3"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_21_3"), 1, allocator);
//
//        _dataStar.AddMember(StringRef("level_1_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_2_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_3_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_4_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_5_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_6_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_7_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_8_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_9_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_10_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_11_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_12_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_13_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_14_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_15_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_16_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_17_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_18_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_19_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_20_4"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_21_4"), 1, allocator);
//        
//        _dataStar.AddMember(StringRef("level_1_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_2_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_3_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_4_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_5_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_6_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_7_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_8_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_9_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_10_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_11_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_12_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_13_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_14_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_15_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_16_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_17_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_18_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_19_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_20_5"), 1, allocator);
//        _dataStar.AddMember(StringRef("level_21_5"), 1, allocator);
        
		rapidjson::StringBuffer sb;
		rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
		_dataStar.Accept(writer);
        GameSingleton::getInstance()->setCurrentState(GameState::sUpdateStar);
        
		NativeUtils::updateData(USER_DATA, sb.GetString());
	}

	for (auto itr = _dataStar.MemberBegin(); itr != _dataStar.MemberEnd();
			++itr) {
		_totalStar += itr->value.GetInt();
	}

}

void DataManager::updateStar(int land, int level, int star) {

    GameSingleton::getInstance()->setCurrentState(GameState::sUpdateStar);
	std::string st_level = StringUtils::format("level_%d_%d", level, land);
	Document::AllocatorType& allocator = _dataStar.GetAllocator();
	if (_dataStar.HasMember(st_level.c_str())) {
		if (_dataStar[st_level.c_str()].GetInt() < star) {

			_dataStar.RemoveMember(st_level.c_str());
            _dataStar.AddMember(StringRef(st_level.c_str()), star, allocator);
			rapidjson::StringBuffer sb;
			rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
			_dataStar.Accept(writer);
			_dataStar.Parse<0>(sb.GetString());
			NativeUtils::updateData(USER_DATA, sb.GetString());
		}
	} else {
		_dataStar.AddMember(StringRef(st_level.c_str()), star, allocator);
		rapidjson::StringBuffer sb;
		rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
		_dataStar.Accept(writer);
		_dataStar.Parse<0>(sb.GetString());
		NativeUtils::updateData(USER_DATA, sb.GetString());

	}
    
    _totalStar = 0;
    
    for (auto itr = _dataStar.MemberBegin(); itr != _dataStar.MemberEnd();
         ++itr) {
        _totalStar += itr->value.GetInt();
    }
    
	NativeUtils::updateData(USER_SCORE, _totalStar);
    NativeUtils::submitScore(LEAD_STAR_MODE, _totalStar);
//	}
}

int DataManager::getStar(int land, int level) {

	const std::string st_level = StringUtils::format("level_%d_%d", level, land);
    
	if (_dataStar.HasMember(st_level.c_str())) {
        
		return _dataStar[st_level.c_str()].GetInt();
	}
    else
        return -1;
	
}

void DataManager::loadGameSetting() {
	std::string dataPath = FileUtils::getInstance()->getWritablePath()
			+ "setting.json";
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(
			dataPath);

	if (FileUtils::getInstance()->isFileExist(fullpath)) {
		ssize_t filesize;
		char* data;
		std::string content;
		data = (char*) FileUtils::getInstance()->getFileData(fullpath.c_str(),
				"r", &filesize);
		content.append(data);
		content = content.substr(0, filesize);
		_gameSettingDoc.Parse<0>(content.c_str());
	} else {
		std::string sound = "sound";
		std::string control = "control";
		std::string music = "music";
		std::string difficult = "difficult";
		std::string max_level = "max_level";
		std::string current_level = "current_level";

		Document::AllocatorType& allocator = _gameSettingDoc.GetAllocator();

		_gameSettingDoc.SetObject();
		_gameSettingDoc.AddMember(StringRef(sound.c_str()), 100, allocator);
		_gameSettingDoc.AddMember(StringRef(music.c_str()), 100, allocator);
		_gameSettingDoc.AddMember(StringRef(difficult.c_str()), 1, allocator);
		_gameSettingDoc.AddMember(StringRef(control.c_str()), true, allocator);
		_gameSettingDoc.AddMember(StringRef(max_level.c_str()), 1, allocator);
		_gameSettingDoc.AddMember(StringRef(current_level.c_str()), 1, allocator);

		this->writeToJsonFile(fullpath, _gameSettingDoc);
	}
}

void DataManager::loadLevelsCleared() {
	std::string dataPath = FileUtils::getInstance()->getWritablePath()
			+ "levels_cleared.json";
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(
			dataPath);

	if (FileUtils::getInstance()->isFileExist(fullpath)) {
		ssize_t filesize;
		char* data;
		std::string content;
		data = (char*) FileUtils::getInstance()->getFileData(fullpath.c_str(),
				"r", &filesize);
		content.append(data);
		content = content.substr(0, filesize);
		_levelsClearedDoc.Parse<0>(content.c_str());
	} else {
		_levelsClearedDoc.SetObject();
		this->writeToJsonFile(fullpath, _levelsClearedDoc);
	}
}

void DataManager::loadGameInfo() {
	std::string dataPath = FileUtils::getInstance()->getWritablePath()
			+ "game_info.json";
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(
			dataPath);

	if (FileUtils::getInstance()->isFileExist(fullpath)) {
		ssize_t filesize;
		char* data;
		std::string content;
		data = (char*) FileUtils::getInstance()->getFileData(fullpath.c_str(),
				"r", &filesize);
		content.append(data);
		content = content.substr(0, filesize);
		_gameInfo.Parse<0>(content.c_str());
	} else {
		std::string first_activity = "first_activity";
		std::string last_activity = "last_activity";
		Document::AllocatorType& allocator = _gameInfo.GetAllocator();

		double activity1 = time(NULL);
		double activity2 = time(NULL);
		_gameInfo.SetObject();
		_gameInfo.AddMember(StringRef(first_activity.c_str()), activity1, allocator);
		_gameInfo.AddMember(StringRef(last_activity.c_str()), activity2, allocator);
		this->writeToJsonFile(fullpath, _gameInfo);
	}
}

void DataManager::loadInventory() {

}

void DataManager::loadAchievement() {

}

MapData DataManager::getMapDataAtLevel(int land, int level) {
	rapidjson::Document doc = this->loadMapData(land);

	rapidjson::Value &obj = doc[StringUtils::format("map%d", level).c_str()];

	int diamond = obj["diamond"].GetInt();
	int fuel = obj["fuel"].GetInt();
	int enemy = obj["enemy"].GetInt();
	int timeBomb = obj["timebomb"].GetInt();
	int bomb = obj["bomb"].GetInt();

	int rocket = obj["rocket"].GetInt();
	int mine = obj["mine"].GetInt();
	int time = obj["time"].GetInt();

	return MapData(diamond, fuel, enemy, time, bomb, timeBomb, rocket, mine);
}

Inventory DataManager::getInventory() {
	return Inventory(_inventory["bombs"].GetInt(), _inventory["mines"].GetInt(),
			_inventory["time_bombs"].GetInt(), _inventory["rockets"].GetInt(),
			_inventory["coins"].GetInt(), _inventory["snow_flakes"].GetInt(),
			_inventory["switch_bombs"].GetInt());
}

std::vector<cocos2d::Vec2> DataManager::getPositionAtLevel(int land) {
	rapidjson::Document doc = loadLevelPositionData(land);
	rapidjson::Value& obj = doc["points"];
	int size = obj.Size();

	std::vector<Vec2> arr;

	for (int i = 0; i < size; i++) {
		arr.push_back(
				cocos2d::Vec2(obj[i]["x"].GetInt(), obj[i]["y"].GetInt()));
	}

	return arr;
}

void DataManager::saveGameSetting() {
	std::string dataPath = FileUtils::getInstance()->getWritablePath()
			+ "setting.json";
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(
			dataPath);
	this->writeToJsonFile(fullpath, _gameSettingDoc);
}
