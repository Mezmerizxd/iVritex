#include "AbstractSubmenu.hpp"
#include "RegularSubmenu.hpp"

namespace big::Ui1 {
	enum Submenu : std::uint32_t {
		Home,
		Self,
		Network,
		Weapons,
		VehicleSpawner,
		VehicleOptions,
		Teleport,
		Recovery,
		Credits,
		Settings
	};
	struct Color
	{
		std::uint8_t r{ 255 };
		std::uint8_t g{ 255 };
		std::uint8_t b{ 255 };
		std::uint8_t a{ 255 };
	};
	struct Vector2
	{
		float x{};
		float y{};
	};
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};
	enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1,
		Custom = 2
	};
	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			return true;
		}
		return false;
	}
}

namespace big::Ui1 {
	class Ui {

	public:
		explicit Ui() = default;
		~Ui() noexcept = default;
		Ui(Ui const&) = delete;
		Ui(Ui&&) = delete;
		Ui& operator=(Ui const&) = delete;
		Ui& operator=(Ui&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void AddSubmenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}
		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		static void script_func();

	public:
		std::mutex m_Mutex;
		bool m_Opened = true;
		bool m_MouseLocked = false;

		float m_PosX = 0.8f;
		float m_PosY = 0.1f;
		float m_Width = 0.20f;

		float m_DrawBaseY{};

		std::size_t m_OptionsPerPage = 11;

		bool m_Sounds = true;

		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 150;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_VerticalDelay2 = 520;
		std::int32_t m_HorizontalDelay = 120;

		// Colours
		Color iVritex_Color{ 70, 100, 150, 255 };

		// Header
		float m_HeaderHeight = 0.1f;
		bool m_HeaderText = false;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::ChaletLondon;
		Color m_HeaderBackgroundColor = iVritex_Color;
		Color m_HeaderTextColor{ 255,255,255, 255 };
		HeaderType m_HeaderType = HeaderType::Static;
		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 0, 186, 255, 255 };
		Color m_HeaderGradientColorRight{ 252, 0, 255, 255 };

		// Submenu bar
		float m_SubmenuBarHeight = 0.03f;
		float m_SubmenuBarTextSize = 0.35f;
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 30, 30, 30, 255 };
		Color m_SubmenuBarTextColor{ 255,255,255, 255 };

		// Options
		float m_OptionHeight = 0.035f;
		float m_OptionTextSize = 0.34f;
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = 2.1f;
		bool m_OptionGradientTransparent = false;
		bool m_OptionGradientFlip = false;
		float m_OptionGradientStretch = 0.f;
		float m_OptionGradientFiller = 0.f;
		Color m_OptionGradientColorLeft{ 40, 40, 40, 255 };
		Color m_OptionGradientColorRight{ 0, 0, 0, 225 };
		Color m_OptionSelectedTextColor{ 255, 255, 255, 255 };
		Color m_OptionUnselectedTextColor{ 255,255,255, 255 };
		Color m_OptionSelectedBackgroundColor{ 40, 40, 40, 255 };
		Color m_OptionSelectedScrollColor = iVritex_Color;
		Color m_OptionUnselectedScrollColor{ 0, 0, 0, 0 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 225 };

		// Footer
		float m_FooterHeight = 0.03f;
		float m_FooterSpriteSize = 0.025f;
		Color m_FooterBackgroundColor{ 30, 30, 30, 255 };
		Color m_FooterSpriteColor = iVritex_Color;
		Color m_FooterTextColor = iVritex_Color;
		float m_FooterTextSize = 0.30f;
		Font m_FooterFont = Font::ChaletLondon;

		// Description
		float m_DescriptionHeightPadding = 0.0f;
		float m_DescriptionHeight = 0.033f;
		float m_DescriptionTextSize = 0.28f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 120 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };

	private:
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;

	public:
		void PurgeTheme();
		void Tick();

		void HandleInput();
		void ResetInput();
		void CheckForInput();

		void DrawHeader();
		void DrawSubmenuBar(AbstractSubmenu* leftText);
		void DrawOption(AbstractOption* opt, bool selected);
		void DrawFooter();
		void DrawDescription();

	private:
		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		float GetTextHeight(Font font, float size);
		Vector2 GetSpriteScale(float size);

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	};
}
namespace big {
	inline std::unique_ptr<Ui1::Ui> g_Ui;
	inline Ui1::Ui g_ui;
}
