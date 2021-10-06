
#pragma once

//public:
namespace ofxImGuiSurfing
{

	//--

	// workaround

	//TODO: a nice idea could be to get the longer param label name width and use this max width to apply to our layouting engine...

	// Some macro sugar to help fix how sliders force autoresize the panel widths.
	// It's a 'rare behaviour' that I am trying to correct doing this.

	//-

	//TODO:
//#define DEFAULT_LAYOUT_BEHAVIOUR // -> Uncomment to use a workaround to weird ImGui auto resize rare layout..

	//-

#ifndef DEFAULT_LAYOUT_BEHAVIOUR
	// A. Relative to panel width

	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x-90);
	#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x>200?ImGui::GetContentRegionAvail().x-110:ImGui::GetContentRegionAvail().x-90);//sometimes looks weird..
	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2);

	#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();
#endif

	//-

	//// B. Using absolute size
	//#define IMGUI_LABELS_WIDTH_DEFAULT 95
	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();

	//-

#ifndef DEFAULT_LAYOUT_BEHAVIOUR
	// C. To bypass and do nothing.
	#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ;
	#define IMGUI_SUGAR_SLIDER_WIDTH_POP ;
#endif

//--

	//TODO: 
	// make simpler namespace. or move outside the class?
	enum SurfingImGuiTypes
	{
		OFX_IM_DEFAULT = 0,	// default style for each widget. (kind of like ofxImGui does)
		OFX_IM_HIDDEN,		// omit widget. don't let spacing there
		OFX_IM_DISABLED,	// make it invisble, preserve the void spacing
		OFX_IM_INACTIVE,	// draws the widget. but makes it inactive. disables mouse control

		//-

		// Bool

		// Button
		OFX_IM_BUTTON_SMALL,
		OFX_IM_BUTTON_BIG,
		OFX_IM_BUTTON_BIG_XXL,
		// Toggle
		OFX_IM_CHECKBOX,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,
		// Border
		OFX_IM_TOGGLE_SMALL_BORDER,
		OFX_IM_TOGGLE_BIG_BORDER,
		OFX_IM_TOGGLE_BIG_XXL_BORDER,
		// Blink border
		OFX_IM_TOGGLE_SMALL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK,
		// Rounded
		OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG,

		//-

		// Float / Int
		OFX_IM_SLIDER,//ImGui standard

		//TODO:
		// Big H/V Sliders

		OFX_IM_HSLIDER_BIG,
		OFX_IM_HSLIDER_BIG_NO_NAME,
		OFX_IM_HSLIDER_BIG_NO_NUMBER,
		OFX_IM_HSLIDER_BIG_NO_LABELS,
		OFX_IM_HSLIDER_SMALL,
		OFX_IM_HSLIDER_SMALL_NO_NAME,
		OFX_IM_HSLIDER_SMALL_NO_NUMBER,
		OFX_IM_HSLIDER_SMALL_NO_LABELS,
		OFX_IM_HSLIDER,
		OFX_IM_HSLIDER_NO_NAME,
		OFX_IM_HSLIDER_NO_NUMBER,
		OFX_IM_HSLIDER_NO_LABELS,

		OFX_IM_VSLIDER,
		OFX_IM_VSLIDER_NO_NAME,
		OFX_IM_VSLIDER_NO_NUMBER,
		OFX_IM_VSLIDER_NO_LABELS,

		OFX_IM_PROGRESS_BAR,
		OFX_IM_PROGRESS_BAR_NO_TEXT,//TODO:
		OFX_IM_STEPPER,
		OFX_IM_DRAG,
		OFX_IM_KNOB,
		OFX_IM_KNOB_TRAIL,
		OFX_IM_COMBO,//TODO: multiple controls for fine tweak: slider + drag + stepper

		//-

		// Strings
		OFX_IM_TEXT_DISPLAY,
		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_BIG,

		//-

		// Colors
		OFX_IM_COLOR_INPUT,
		OFX_IM_COLOR_NO_ALPHA,//without the alpha control
		OFX_IM_COLOR_BOX,//small box color without controls
		OFX_IM_COLOR_BOX_FULL_WIDTH,
		OFX_IM_COLOR_BOX_FULL_WIDTH_BIG,

		//-

		// Multidim
		//TODO: for glm::vec
		OFX_IM_MULTIDIM_SPLIT_SLIDERS,
		//OFX_IM_MULTIDIM_SPLIT_STEPPERS,//TODO:
		//OFX_IM_MULTIDIM_SPLIT_DRAGS,

		OFX_IM_NUM_TYPES
	};

	//--

	//TODO:
	// Centralize name types
	// Try to mix ImHelpers with ImTypes..
	enum SurfingImGuiTypesGroups
	{
		OFX_IM_GROUP_DEFAULT = 0,
		OFX_IM_GROUP_COLLAPSED,
		OFX_IM_GROUP_TREE_EX,
		OFX_IM_GROUP_TREE,
		OFX_IM_GROUP_SCROLLABLE,
		OFX_IM_GROUP_HIDDEN_HEADER, // hide hidder. TODO; fails on first group. not working
		OFX_IM_GROUP_HIDDEN, // hide header and all the content

		OFX_IM_GROUP_NUM_TYPES
	};

	inline static std::string getSurfingImGuiTypesGroupsName(int i)
	{
		string _groupInfo;
		if (i == 0) _groupInfo = "OFX_IM_GROUP_DEFAULT";
		else if (i == 1) _groupInfo = "OFX_IM_GROUP_COLLAPSED";
		else if (i == 2) _groupInfo = "OFX_IM_GROUP_TREE_EX";
		else if (i == 3) _groupInfo = "OFX_IM_GROUP_TREE";
		else if (i == 4) _groupInfo = "OFX_IM_GROUP_SCROLLABLE";
		else if (i == 5) _groupInfo = "OFX_IM_GROUP_HIDDEN_HEADER";

		return _groupInfo;
	}
}
