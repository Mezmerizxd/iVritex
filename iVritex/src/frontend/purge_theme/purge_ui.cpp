#include "natives.hpp"
#include "Timer.hpp"
#include "features.hpp"
#include "RegularOption.hpp"
#include "SubOption.hpp"
#include "BoolOption.hpp"
#include "ChooseOption.hpp"
#include "NumberOption.hpp"

namespace big::Ui1
{

	void Ui::PurgeTheme()
	{
		// Home
		g_ui.AddSubmenu<RegularSubmenu>("Home", Home, [](RegularSubmenu *sub)
																		{
			sub->AddOption<SubOption>("Self", nullptr, Self);	
			sub->AddOption<SubOption>("Network", nullptr, Network);
			sub->AddOption<SubOption>("Weapons", nullptr, Weapons);
			sub->AddOption<SubOption>("Vehicle Spawner", nullptr, VehicleSpawner);
			sub->AddOption<SubOption>("Vehicle Options", nullptr, VehicleOptions);
			sub->AddOption<SubOption>("Teleport", nullptr, Teleport);
			sub->AddOption<SubOption>("Recovery", nullptr, Recovery);
			sub->AddOption<SubOption>("Credits", nullptr, Credits);
			sub->AddOption<SubOption>("Settings", nullptr, Settings); });

		// Self
		g_ui.AddSubmenu<RegularSubmenu>("Self", Self, [](RegularSubmenu *sub)
																		{
			sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &features::game.Self_Godmode, BoolDisplay::DefaultToggles);
			sub->AddOption<BoolOption<bool>>("No Clip", nullptr, &features::game.Self_Noclip, BoolDisplay::DefaultToggles); });

		// Settings
		g_ui.AddSubmenu<RegularSubmenu>("Settings", Settings, [](RegularSubmenu *sub)
																		{
																			// sub->AddOption<NumberOption<std::uint8_t>>("[Theme] R", nullptr, &g_Ui->iVritex_Color.r, '\0', static_cast<std::uint8_t>(255));
																			// sub->AddOption<NumberOption<std::uint8_t>>("[Theme] G", nullptr, &g_Ui->iVritex_Color.g, '\0', static_cast<std::uint8_t>(255));
																			// sub->AddOption<NumberOption<std::uint8_t>>("[Theme] B", nullptr, &g_Ui->iVritex_Color.b, '\0', static_cast<std::uint8_t>(255));
																		});
	}

}

namespace big::Ui1
{
	void Ui::Tick()
	{
		std::lock_guard lock(m_Mutex);

		CheckForInput();
		HandleInput();

		if (m_Opened)
		{
			CONTROLS::DISABLE_CONTROL_ACTION(0, 27, true);

			m_DrawBaseY = m_PosY;
			DrawHeader();

			PurgeTheme();

			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();

				DrawSubmenuBar(sub);

				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						DrawOption(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
			}

			DrawFooter();
			DrawDescription();
		}
	}

	void Ui::HandleInput()
	{
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			m_Opened ^= true;

			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}
		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (m_Opened && m_BackKeyPressed && backTimer.Update())
		{
			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() <= 1)
			{
				m_Opened = false;
			}
			else
			{
				m_SubmenuStack.pop();
			}
		}
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (m_Opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}
	void Ui::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}
	void Ui::CheckForInput()
	{
		ResetInput();
		m_OpenKeyPressed = IsKeyPressed(VK_F4);
		m_BackKeyPressed = IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = IsKeyPressed(VK_UP);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void Ui::DrawHeader()
	{
		switch (m_HeaderType)
		{
		case HeaderType::Static:
			DrawRect(
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width,
					m_HeaderHeight,
					iVritex_Color);
			break;
		case HeaderType::Custom:
			GRAPHICS::DRAW_SPRITE("Themes", "PurgeTheme", m_PosX, m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width, m_HeaderHeight, 0.f, 255, 255, 255, 255);
			break;
		case HeaderType::Gradient:
			for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite(
						"aircraft_dials",
						"aircraft_dials_g0",
						m_PosX - (m_HeaderGradientStretch / 2.f),
						m_DrawBaseY + (m_HeaderHeight / 2.f),
						m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
						m_HeaderHeight,
						m_HeaderGradientColorRight,
						m_HeaderGradientFlip ? 0.f : 180.f);
				DrawSprite(
						"aircraft_dials",
						"aircraft_dials_g0",
						m_PosX + (m_HeaderGradientStretch / 2.f),
						m_DrawBaseY + (m_HeaderHeight / 2.f),
						m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
						m_HeaderHeight,
						m_HeaderGradientColorLeft,
						m_HeaderGradientFlip ? 180.f : 0.f);
			}
			break;
		}

		if (m_HeaderText)
		{
			DrawCenteredText(
					"Menu",
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
					m_HeaderTextSize,
					m_HeaderFont,
					m_HeaderTextColor,
					false, true);
		}

		m_DrawBaseY += m_HeaderHeight;
	}
	void Ui::DrawSubmenuBar(AbstractSubmenu *sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c)
									 { return static_cast<char>(toupper(c)); });

		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

		DrawRect(
				m_PosX,
				m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
				m_Width, m_SubmenuBarHeight,
				m_SubmenuBarBackgroundColor);
		DrawLeftText(
				&leftText[0],
				m_PosX - (m_Width / m_SubmenuBarPadding),
				m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
				m_SubmenuBarTextSize, m_SubmenuBarFont,
				iVritex_Color,
				false, true);

		m_DrawBaseY += m_SubmenuBarHeight;
	}
	void Ui::DrawOption(AbstractOption *opt, bool selected)
	{
		DrawRect( // Option background
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f),
				m_Width,
				m_OptionHeight,
				m_OptionUnselectedBackgroundColor);

		for (std::size_t i = 0; i < (m_OptionGradientTransparent ? 1 : 20); ++i)
		{
			DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX - (m_OptionGradientStretch / 2.f),
					m_DrawBaseY + (m_OptionHeight / 2.f),
					m_Width + m_OptionGradientStretch + m_OptionGradientFiller,
					m_OptionHeight,
					selected ? m_OptionGradientColorRight : m_OptionUnselectedScrollColor,
					m_OptionGradientFlip ? 0.f : 180.f);
			DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX - (m_OptionGradientStretch / 2.f),
					m_DrawBaseY + (m_OptionHeight / 2.f),
					m_Width + m_OptionGradientStretch + m_OptionGradientFiller,
					m_OptionHeight,
					selected ? m_OptionGradientColorLeft : m_OptionUnselectedScrollColor,
					m_OptionGradientFlip ? 180.f : 0.f);
		}

		DrawRect(							// Scroller
				m_PosX - 0.0975f, // 0.6875f
				m_DrawBaseY + (m_OptionHeight / 2.f),
				0.005f,
				m_OptionHeight,
				selected ? m_OptionSelectedScrollColor : m_OptionUnselectedScrollColor);
		DrawLeftText( // Option text
				opt->GetLeftText(),
				m_PosX - (m_Width / m_OptionPadding) + 0.0035f,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
		DrawRightText( // Arrows
				opt->GetRightText(),
				m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);

		if (opt->GetFlag(OptionFlag::Enterable))
		{
			DrawRightText(
					">>",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
					m_OptionTextSize,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
		}

		m_DrawBaseY += m_OptionHeight;
	}
	void Ui::DrawFooter()
	{
		DrawRect(
				m_PosX,
				m_DrawBaseY + (m_FooterHeight / 2.f),
				m_Width,
				m_FooterHeight,
				m_FooterBackgroundColor);

		DrawLeftText( // Option text
				"By Mezmerizxd",
				m_PosX - (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.3f),
				m_FooterTextSize,
				m_FooterFont,
				m_FooterTextColor,
				false, false);

		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char *texture = "shop_arrows_upanddown";

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetSelectedOption() == 0)
			{
				rotation = 90.f;
				texture = "arrowright";
				size *= 0.8f;
			}
			else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
			{
				rotation = 270.f;
				texture = "arrowright";
				size *= 0.8f;
			}
		}

		auto sizee = GetSpriteScale(size);

		DrawSprite(
				"commonmenu",
				texture,
				m_PosX + 0.09f,
				m_DrawBaseY + (m_FooterHeight / 2.f),
				sizee.x,
				sizee.y,
				m_FooterSpriteColor,
				rotation);

		m_DrawBaseY += m_FooterHeight;
	}
	void Ui::DrawDescription()
	{
		const char *description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += m_DescriptionHeightPadding;

		DrawRect(
				m_PosX,
				m_DrawBaseY + (m_DescriptionHeight / 2.f),
				m_Width,
				m_DescriptionHeight,
				m_DescriptionBackgroundColor);

		auto spriteSize = GetSpriteScale(m_DescriptionSpriteSize);
		DrawSprite(
				"shared", "info_icon_32",
				m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x / 2.f),
				m_DrawBaseY + (m_DescriptionHeight / 2.f),
				spriteSize.x,
				spriteSize.y,
				m_DescriptionSpriteColor,
				0.f);

		DrawLeftText(
				description,
				m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x * 1.15f),
				m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
				m_DescriptionTextSize,
				m_DescriptionFont,
				m_DescriptionTextColor,
				false, false);

		m_DrawBaseY += m_DescriptionHeight;
	}

	void Ui::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a);
	}
	void Ui::DrawSprite(const char *dict, const char *texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}
	void Ui::DrawLeftText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_SCALE(size, size);
		UI::SET_TEXT_FONT(static_cast<int>(font));
		UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			UI::SET_TEXT_OUTLINE();
		if (shadow)
			UI::SET_TEXT_DROP_SHADOW();

		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
	}
	void Ui::DrawRightText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_WRAP(0.f, x);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}
	void Ui::DrawCenteredText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}
	float Ui::GetTextHeight(Font font, float size)
	{
		return UI::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}
	Vector2 Ui::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return {(static_cast<float>(y) / static_cast<float>(x)) * size, size};
	}

}
