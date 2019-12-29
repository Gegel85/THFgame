//
// Created by Gegel85 on 23/12/2019.
//

#include <TGUI/TGUI.hpp>
#include "GuiUtils.hpp"

namespace TouhouFanGame
{
	tgui::Button::Ptr makeButton(const std::string &content, tgui::Layout x, tgui::Layout y, const std::function<void (tgui::Button::Ptr button)> &handler, int width, int height)
	{
		tgui::Button::Ptr button = tgui::Button::create(content);

		button->setPosition(std::move(x), std::move(y));
		if (handler)
			button->connect("pressed", handler, button);
		if (height && width)
			button->setSize(width, height);
		return button;
	}

	tgui::TextBox::Ptr makeTextBox(tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height, const std::string &placeholder)
	{
		tgui::TextBox::Ptr box = tgui::TextBox::create();

		box->setPosition(std::move(x), std::move(y));
		box->setSize({width, height});
		box->setText(placeholder);
		box->setReadOnly(true);
		box->setEnabled(false);
		return box;
	}

	tgui::EditBox::Ptr makeTypeBox(tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height, const std::string &placeholder, const std::string &inputValidator)
	{
		tgui::EditBox::Ptr box = tgui::EditBox::create();

		box->setPosition(std::move(x), std::move(y));
		box->setSize({std::move(width), std::move(height)});
		box->setText(placeholder);
		box->setReadOnly(false);
		box->setInputValidator(inputValidator);
		return box;
	}

	tgui::Picture::Ptr makePicture(const tgui::Texture &texture, tgui::Layout x, tgui::Layout y, tgui::Layout width, tgui::Layout height)
	{
		tgui::Picture::Ptr pic = tgui::Picture::create(texture);

		pic->setPosition(std::move(x), std::move(y));
		pic->setSize({std::move(width), std::move(height)});
		pic->ignoreMouseEvents();
		return pic;
	}

	void showLoadFileWindow(tgui::Gui &gui, const std::string &title, const std::string &loadButtonCaption, unsigned short defaultValue, const std::function<void(unsigned short)> &onLoad)
	{
		auto filenameWindow = openWindowWithFocus(gui);

		filenameWindow->setTitle(title);
		filenameWindow->setSize(400, 100);
		filenameWindow->loadWidgetsFromFile("assets/gui/LoadFile.txt");
		filenameWindow->setFocused(true);

		auto box = filenameWindow->get<tgui::EditBox>("CurrentMap");
		auto slider = filenameWindow->get<tgui::Slider>("MapNumber");
		auto buttonLoad = filenameWindow->get<tgui::Button>("BtnLoad");
		auto buttonCancelLoadingImage = filenameWindow->get<tgui::Button>("BtnCancel");

		box->setText(std::to_string(defaultValue));
		buttonLoad->setText(loadButtonCaption);
		slider->setMinimum(0);
		slider->setMaximum(65535);
		slider->setValue(defaultValue);
		slider->connect("ValueChanged", [slider, box]() {
			slider->setValue(static_cast<int>(slider->getValue()));
			box->setText(std::to_string(static_cast<int>(slider->getValue())));
		});

		box->connect("TextChanged", [box, slider]{
			try {
				slider->setValue(std::stol(static_cast<std::string>(box->getText())));
			} catch (std::exception &) {
				slider->setValue(0);
				box->setText("0");
			}
		});
		buttonCancelLoadingImage->connect("pressed", [filenameWindow]{
			filenameWindow->close();
		});
		buttonLoad->connect("pressed", [filenameWindow, slider, onLoad]{
			onLoad(slider->getValue());
			filenameWindow->close();
		});
	}

	tgui::Label::Ptr makeLabel(const std::string &content, tgui::Layout x, tgui::Layout y)
	{
		auto label = tgui::Label::create(content);

		label->setPosition(x, y);
		return label;
	}

	tgui::ChildWindow::Ptr openWindowWithFocus(tgui::Gui &gui, const std::function<void()> &closeHandle)
	{
		auto panel = tgui::Panel::create({"100%", "100%"});
		panel->getRenderer()->setBackgroundColor({0, 0, 0, 175});
		gui.add(panel);

		auto window = tgui::ChildWindow::create();
		window->setPosition("(&.w - w) / 2", "(&.h - h) / 2");
		gui.add(window);

		window->setFocused(true);

		const bool tabUsageEnabled = gui.isTabKeyUsageEnabled();
		auto closeWindow = [&gui, window, panel, tabUsageEnabled, closeHandle]{
			gui.remove(window);
			gui.remove(panel);
			gui.setTabKeyUsageEnabled(tabUsageEnabled);
			if (closeHandle)
				closeHandle();
		};

		panel->connect("Clicked", closeWindow);
		window->connect({"Closed", "EscapeKeyPressed"}, closeWindow);

		return window;
	}
}