#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

//--------------------------------------------------------------

// this header includes all the ImGui classes: layout, helpers and all my Surfing widgets.

//---------
// HEADERS
//---------

#include "ImGui/ofxSurfing_ImGui_ofHelpers.h"

#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"

#include "ImGui/ofxSurfing_ImGui_Widgets.h"
//#include "ImGui/ofxSurfing_ImGui_WidgetsButtons.h"
//#include "ImGui/ofxSurfing_ImGui_WidgetsExtra.h"
//#include "ImGui/ofxSurfing_ImGui_WidgetsKnob.h"
//#include "ImGui/ofxSurfing_ImGui_WidgetsRangeSlider.h"
//#include "ImGui/ofxSurfing_ImGui_WidgetsBezier.h"
//#include "ImGui/dear_widgets/dear_widgets.h"

#include "ImGui/ofxSurfing_ImGui_ThemesEditor.h"
//#include "ImGui/ofxSurfing_ImGui_Themes.h"
//#include "ImGui/themes/ThemeSequentity.inl"



using namespace ofxImGuiSurfing;

//--------------------------------------------------------------

/*
	EXAMPLE SNIPPETS
	----------------

	Typical basic usage

	Copy paste all this to your ofApp
	or you can use ofxSurfing_ImGui_Manager that bundles all this code

	Content:
	1. LAYOUT MANGER: SIMPLIFY THE WINDOW/PANELS/LAYOUT PROCESS.
	2. ofxImGui BASIC BOILERPLATE.
	3. RAW IMGUI: WINDOW, PANELS, AND SUB PANELS AND DIFFERENT TREES MODES.
	4. WINDOW PANEL SHAPE: GET WINDOW POSITION FOR ADVANCED LAYOUT LINKED TO OTHER WINDOWS/GUI'S.
	5. MORE RAW IMGUI SNIPPETS
*/


//--------------------------------------------------------------


// LEARN HOW TO CREATE
// WINDOWS, PANELS, AND SUB PANELS AND DIFFERENT TREES MODES

/*
	//--

	// 1. CREATE A WINDOW

	// WINDOWS USING RAW ImGui

	// 1.0 SIMPLE

	ImGui::Begin("myWindow);
	{ }
	ImGui::End();

	//--

	// 1.1 WINDOW WITH NAME WITH FLAGS

	string _name = "myWindow";
	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	ImGui::Begin(_name.c_str(), NULL, _flagw);
	{ }
	ImGui::End();

	//--

	// 1.2 WINDOW USING ofxImGui

	// (DEPRECATED. Better to not use like this)

	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	string _name = "myWindow";
	ofxImGui::Settings mainSettings = ofxImGui::Settings();
	if (ofxImGui::BeginWindow(_name.c_str(), mainSettings, _flagw))
	{ }
	ofxImGui::EndWindow(mainSettings);

	//--

	// 2. TREES

	// 2.1 TREE

	if (ImGui::TreeNode("_Tree"))
	{
		//..
		ImGui::TreePop();
	}

	//--

	// 2.2 COLLAPSING PANEL

	bool bOpen = false;
	ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
	if (ImGui::CollapsingHeader("_Collapsing", _flagw))
	{
		//..
	}

	//--

	// 2.3 treeEx - TREE WITH FLAGS

	bool bOpen = true;
	ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
	_flagt |= ImGuiTreeNodeFlags_Framed;
	if (ImGui::TreeNodeEx("_TreeEx", _flagt))
	{
		//..
		ImGui::TreePop();
	}

	//--

*/


//--------------------------------------------------------------


/*

// 1. LAYOUT MANGER

// .h
#include "ofxSurfingImGui.h"	// -> Add all classes. You can also simplify picking what you want to use.
ofxSurfing_ImGui_Manager guiManager; // In MODE A ofxGui will be instatiated inside the class

// .cpp
// setup()
guiManager.setImGuiAutodraw(true); // -> required when one single ImGui instance only to respect autodraw and mouse interaction!
guiManager.setup(); // ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).

//--------------------------------------------------------------
void drawImGui()
void ofApp::drawImGui()
{
	guiManager.begin(); // global begin
	{
		{
			string n = "Show Windows";
			static bool bOpenMain = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			guiManager.beginWindow(n.c_str(), &bOpenMain, window_flags);
			{
				float _h = WIDGETS_HEIGHT;
				float _w100 = getWidgetsWidth(1);
				float _w50 = getWidgetsWidth(2);

				ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpenMain);

				//-

				// EXTRA MENU
				{
					ImGui::Dummy(ImVec2(0, 5)); // spacing

					ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
					if (guiManager.bExtra)
					{
						ImGui::Indent();

						// add your extra (hidden by default) controls
						//ofxImGuiSurfing::AddBigToggle(SHOW_Plot, _w100, _h / 2, false);

						//--

						ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
						if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();

						ImGui::Unindent();
					}
				}
			}
			guiManager.endWindow();
		}

		{
			static bool bOpenMain = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			string n = "Window 4";
			guiManager.beginWindow(n.c_str(), &bOpenMain, window_flags);
			{
				// PARAMS GHROUP
				{
					bool bOpen = true;
					ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
					_flagt |= ImGuiTreeNodeFlags_Framed;
					if (ImGui::TreeNodeEx("Block Render", _flagt))
					{
						ImGuiTreeNodeFlags flagst;
						flagst = ImGuiTreeNodeFlags_None;
						flagst |= ImGuiTreeNodeFlags_DefaultOpen;
						flagst |= ImGuiTreeNodeFlags_Framed;
						ofxImGuiSurfing::AddGroup(params_Render, flagst);

						ImGui::TreePop();
					}
				}
			}
			guiManager.endWindow();
		}

	}
	guiManager.end(); // global end
}

*/


//--------------------------------------------------------------


/*

// 2. "RAW" ofxImGui BASIC BOILERPLATE

//ofApp.h

//#include "ofxSurfingImGui.h"

void setup_ImGui();
void draw_ImGui();
ofxImGui::Gui gui;
ofxImGui::Settings mainSettings = ofxImGui::Settings();
ImFont* customFont = nullptr;
ofParameter<bool> bGui{ "Show Gui", true };
ofParameter<bool> bAutoResize{ "Auto Resize", true };
ofParameter<bool> bMouseOverGui{ "Mouse Locked", false };
ofParameter<bool> auto_lockToBorder{ "Lock GUI", false };

//-

//ofApp.cpp

setup_ImGui();
draw_ImGui();

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bAutoDraw = true;
	bool bRestore = true;
	bool bMouse = false;
	gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	//-

	// font
	std::string fontName;
	float fontSizeParam;
	fontName = "telegrama_render.otf"; //  WARNING: will crash if font not present!
	fontSizeParam = 11;

	//-

	std::string _path = "assets/fonts/"; // assets folder
	customFont = gui.addFont(_path + fontName, fontSizeParam, nullptr, normalCharRanges);
	io.FontDefault = customFont;

	// theme
	ofxSurfingHelpers::ImGui_ThemeMoebiusSurfing();
	//ofxSurfingHelpers::ImGui_ThemeModernDark();
}

//--------------------------------------------------------------
void ofApp::draw_ImGui()
{
	guiManager.begin();
	{
		// panels minimal sizes
		float xx = 10;
		float yy = 10;
		float ww = PANEL_WIDGETS_WIDTH;
		float hh = PANEL_WIDGETS_HEIGHT;
		int pad = 10;

		// helpers to assist layout widget sizes to fit panel width or height
		// example:
		// declare size vars for typical sizes 100%, 50%, 33% ..etc
		// pass external variables as references

		// APPROACH A
		// widgets sizes
		float _w100;
		float _w50;
		float _w33;
		float _w25;
		float _h = WIDGETS_HEIGHT;
		_w100 = getWidgetsWidth(1);
		_w50 = getWidgetsWidth(2);
		_w33 = getWidgetsWidth(3);
		_w25 = getWidgetsWidth(4);

		//// APPROACH B
		//// widgets sizes
		//float _spcx; // space between widgets
		//float _spcy; // space between widgets
		//float _w100; // full width
		//float _h100; // full height
		//float _w99; // a bit less than full width
		//float _w50; // half width
		//float _w33; // third width
		//float _w25; // quarter width
		//float _h; // standard height
		//// snippet to use inside ImGui window/tree adapting for his shape
		//// every indented sub tree/folder of a gui window panel can have different/less width, so we need to update sizes with the below method:
		//ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

		//--

		// SET POSITION AND SIZE OF A WINDOW PANEL

		float xx = 0;
		float yy = 0;
		float ww = 0;
		float hh = 0;
		ImGuiCond flagsCond = ImGuiCond_None;
		flagsCond |= ImGuiCond_FirstUseEver;
		ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
		ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
		// xx + = ww + pad;

		//--

		// CREATE WINDOW
	
		ImGuiWindowFlags flagsw = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) flagsw |= ImGuiWindowFlags_AlwaysAutoResize;
		flagsw |= ImGuiCond_FirstUseEver;

		n = params.getName();

		guiManager.beginWindow(n.c_str(), &bOpenMain, flagsw);
		{
			widgetsManager.refreshPanelShape();

			// A
			_w100 = getWidgetsWidth(1);
			_w50 = getWidgetsWidth(2);
			_w33 = getWidgetsWidth(3);
			_w25 = getWidgetsWidth(4);

			// B
			//ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

			// 1. param
			//ImGui::PushItemWidth(-100);
			//ofxImGuiSurfing::AddParameter(_param);
			//ImGui::PopItemWidth();

			// 2. buttons
			//if (ImGui::Button("_Button", ImVec2(_w100, _h / 2))) {}

			// 3. param toggle
			//ofxImGuiSurfing::AddBigToggle(_param, _w100, _h);

			// 4. buttons
			//ImGui::PushButtonRepeat(true);
			//float __w = ofxSurfing::getWidgetsWidth(w, 2); // get width for two widgets per row
			//if (ImGui::Button("<", ImVec2(__w, _h))) {} ImGui::SameLine();
			//if (ImGui::Button(">", ImVec2(__w, _h))) {}
			//ImGui::PopButtonRepeat();

			// 5. spacing
			//ImGui::Dummy(ImVec2(0.0f, 2.0f));

			// group
			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			flagst |= ImGuiTreeNodeFlags_Framed;
			ofxImGuiSurfing::AddGroup(params, flagst);
		}
		guiManager.endWindow();
	}
	guiManager.end();

*/



//--------------------------------------------------------------

// NOTES

// WINDOW PANEL SHAPE 

// Get window position for advanced layout linked position

/*
glm::vec2 pos;
static bool bLockMappgingPanel = true;
ofxImGuiSurfing::ToggleRoundedButton("Lock Mapping panel", &bLockMappgingPanel);
if (bLockMappgingPanel)
{
	float pad = 0;
	auto posx = ImGui::GetWindowPos().x;
	auto posy = ImGui::GetWindowPos().y;
	float __w = ImGui::GetWindowWidth();
	float __h = ImGui::GetWindowHeight();
	pos.x = posx + __w + pad;
	pos.y = posy;
}
*/

//-

//--------------------------------------------------------------

// MORE RAW IMGUI

/*
// 5.1 How to set colors
static float b = 1.0f;
static float c = 0.5f;
static int i = 3;// hue colors are from 0 to 7
ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);
*/

//-

/*
// WINDOW TESTER
{
	ImGuiCond flagsc = ImGuiCond_Appearing;
	static int type = 0;
	if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));      // Vertical only
	if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));      // Horizontal only
	if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
	if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1), ImVec2(500, -1));          // Width 400-500
	if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 400), ImVec2(-1, 500));          // Height 400-500
	ImGui::SetNextWindowPos(ImVec2(10, 10), flagsc);
	ImGui::SetNextWindowSize(ImVec2(100, 100), flagsc);
	ImGui::Begin("Window Control");
	{
		ImGui::SliderInt("TypeConstraints", &type, 0, 4);

		int open_action = -1;
		if (ImGui::Button("Expand"))
			open_action = 0;
		ImGui::SameLine();
		if (ImGui::Button("collapse"))
			open_action = 1;
		ImGui::SameLine();

		if (open_action != -1) {
			ImGui::SetNextWindowCollapsed(open_action != 0);
			//ImGui::SetNextItemOpen(open_action != 0);
		}
	}
	ImGui::End();
}
*/



//--

/*
// An extra begin/end pair
// with snapping
//--------------------------------------------------------------
void Begin(const std::string& name) {
	const int snapSz = 20;
	//const int snapSz = 16;

	auto snap = [=](float value, float snap_threshold) -> float {
		float modulo = std::fmodf(value, snap_threshold);
		float moduloRatio = std::fabsf(modulo) / snap_threshold;
		if (moduloRatio < 0.5f)
			value -= modulo;
		else if (moduloRatio > (1.f - 0.5f))
			value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
		return value;
	};

	ImGui::Begin(name.data());
	if (ImGui::IsItemActive()) {
		auto p = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		float x = snap(p.x, snapSz);
		float y = snap(p.y, snapSz);
		float sizex = snap(size.x, snapSz);
		float sizey = snap(size.y, snapSz);
		ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
	}
}
//--------------------------------------------------------------
void End() {
	ImGui::End();
}

//--

// Another extra begin/end pair
//--------------------------------------------------------------
bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name.c_str(), p_open, flags);
}

//--------------------------------------------------------------
void EndWindow()
{
	ImGui::End();
}
*/

//--

/*
// An extra begin/end pair
// with snapping
bool BeginWindow(std::string name = "Window", bool* p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
void EndWindow();

void Begin(const std::string& name);
void End();
*/

//--

/*		
// ImGui Infos
auto io = ImGui::GetIO();
const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
const auto size = ImGui::CalcTextSize(label.c_str());
ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
ImGui::Text("%s", label.c_str());
*/