#pragma once
#include "BaseOption.hpp"


namespace big::Ui1
{
	enum class BoolDisplay
	{
		CustomToggles,
		DefaultToggles
	};

	template <typename BoolType = bool>
	class BoolOption : public BaseOption<BoolOption<BoolType>>
	{
	public:
		explicit BoolOption(const char* text, const char* description, BoolType* b00l, BoolDisplay displayType, bool displayInverted = false, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_DisplayInverted(displayInverted),
			m_DisplayType(displayType)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}
		~BoolOption() noexcept = default;
		BoolOption(BoolOption const&) = default;
		BoolOption& operator=(BoolOption const&) = default;
		BoolOption(BoolOption&&) = default;
		BoolOption& operator=(BoolOption&&) = default;

		const char* GetRightText() override
		{
			switch (m_DisplayType)
			{
			case BoolDisplay::CustomToggles:
				GRAPHICS::DRAW_SPRITE("Themes",
					(*m_Bool ^ m_DisplayInverted) ? "Toggle_On" : "Toggle_Off",
					g_ui.m_PosX + (g_ui.m_Width / g_ui.m_OptionPadding) - 0.009f,
					g_ui.m_DrawBaseY + (g_ui.m_OptionHeight / 2.f),
					0.023f, 0.023f, 0, 255, 255, 255, 255);
				break;
			case BoolDisplay::DefaultToggles:
				Base::SetRightText((*m_Bool ^ m_DisplayInverted) ? "~g~ON" : "~r~OFF");
				break;
			}

			return Base::GetRightText();
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				*m_Bool = !*m_Bool;
			}

			Base::HandleAction(action);
		}
	private:
		BoolType* m_Bool;
		BoolDisplay m_DisplayType;
		BoolType m_DisplayInverted = false;

		using Base = BaseOption<BoolOption<BoolType>>;
	};
}
