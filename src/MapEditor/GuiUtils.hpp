//
// Created by Gegel85 on 23/12/2019.
//

#ifndef THFGAME_GUIUTILS_HPP
#define THFGAME_GUIUTILS_HPP


#include <TGUI/TGUI.hpp>

namespace TouhouFanGame
{
	tgui::Button::Ptr makeButton(const std::string &content, tgui::Layout x, tgui::Layout y, const std::function<void (tgui::Button::Ptr button)> &handler, int width = 0, int height = 0);
	tgui::TextBox::Ptr makeTextBox(tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height, const std::string &placeholder = "");
	tgui::TextBox::Ptr makeTypeBox(tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height, const std::string &placeholder = "");
	tgui::Picture::Ptr makePicture(const tgui::Texture &texture, tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height);
	tgui::ChildWindow::Ptr openWindowWithFocus(tgui::Gui &gui);
	void showLoadFileWindow(tgui::Gui &gui, const std::string &title, const std::string &loadButtonCaption, unsigned short defaultValue, const std::function<void(unsigned short)> &onLoad);
}


#endif //THFGAME_GUIUTILS_HPP
