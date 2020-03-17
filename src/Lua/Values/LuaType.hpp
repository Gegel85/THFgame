//
// Created by Gegel85 on 17/03/2020.
//

#ifndef THFGAME_LUATYPE_HPP
#define THFGAME_LUATYPE_HPP


namespace TouhouFanGame::Lua
{
	enum LuaType {
		LuaTypeNoValue,
		LuaTypeNil,
		LuaTypeNumber,
		LuaTypeBoolean,
		LuaTypeString,
		LuaTypeTable,
		LuaTypeFunction,
		LuaTypeCFunction,
		LuaTypeThread,
		LuaTypeUserData,
		LuaTypeLightUserData
	};
}


#endif //THFGAME_LUATYPE_HPP
