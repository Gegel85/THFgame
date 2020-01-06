//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_DIALOGCOMPONENT_HPP
#define THFGAME_DIALOGCOMPONENT_HPP


#include "../Component.hpp"
#include "../../Dialogs/DialogMgr.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to entities that can show a dialog box.
	class DialogComponent : public Component {
	private:
		//! @brief The path of the loaded dialog.
		std::string _dialogPath;

	public:
		//! @brief The dialog manager.
		DialogMgr manager;

		//! @brief Changes the dialog path.
		void setDialogPath(const std::string &path);

		//! @brief Returns the current dialog path.
		std::string getDialogPath() const;

		//! @brief Unserializer constructor.
		DialogComponent(std::istream &stream);
		DialogComponent();
		DialogComponent(const std::string &dialogPath);
		~DialogComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_DIALOGCOMPONENT_HPP
