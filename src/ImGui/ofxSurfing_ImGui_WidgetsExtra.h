#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
//#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

#define M_PI 3.14159265358979323846264338327950288

#include "colors/imgui_color_gradient.h"
#include "ImGui/dear_widgets/dear_widgets.h"

// TODO:
// WIP
// to add more uncoming new widgets here

// cute widgets !
// https://github.com/soufianekhiat/DearWidgets

// spin arrows widget
// https://github.com/ocornut/imgui/issues/2649

// spinners, loading bars 
// https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
// https://github.com/ocornut/imgui/issues/1901

// Rotating text and icon demo for dear imgui 
// https://g

// Mosaic project
// https://github.com/d3cod3/ofxVisualProgramming
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/core/imgui_plot.cpp
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/core/imgui_helpers.h


namespace ofxImGuiSurfing
{
	using namespace ImGui;

	// preset clicker matrix buttons
	// index will change when a box is clicked
	//inline bool AddMatrixClicker(ofParameter<int>& _index, string label = "CLICKER", bool bOpen = false, bool bResponsive = true, int amountBtRow = 4)
	inline bool AddMatrixClicker(ofParameter<int>& _index, bool bResponsive = true, int amountBtRow = 4, const bool bDrawBorder = false, float sizey = -1)
	{
		bool cChanged = false;

		if (sizey == -1)
		{
			sizey = ofxImGuiSurfing::getWidgetsHeightRelative();
		}

		//if (bDrawBorder) 
		//{
		ImGuiStyle *style = &ImGui::GetStyle();
		float a = 0.3;
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		//ImVec4 borderLineColor = style->Colors[ImGuiCol_Border];
		//ImVec4 borderLineColor = style->Colors[ImGuiCol_Separator];
		float borderLineWidth = 1.0;
		//}

		//ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		//_flagt |= ImGuiTreeNodeFlags_Framed;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());

		//if (ImGui::TreeNodeEx(label.c_str(), _flagt))
		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float _sizex = 5;

			if (!bResponsive) _sizex = 40;
			else
			{
				_sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				//_sizex = __w100 / amountBtRow - __spcx / amountBtRow - __spcx;
			}

			int _amt = _index.getMax() + 1;
			float sizex;
			//float  sizey;

			if (_amt > amountBtRow)
			{
				sizex = _sizex;
			}
			else
			{
				if (_amt == 1)
				{
					sizex = __w100;
				}
				else
				{
					sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
					//sizex = __w100 / _amt - __spcx / _amt - __spcx;
				}
			}

			//sizey = 40;
			sizex = MAX(5, sizex);

			//-

			//ImGui::Text("PRESET SELECTOR:");
			// toggle button matrix
			ImVec2 sizebt(sizex, sizey);
			// Manually wrapping
			// (we should eventually provide this as an automatic layout feature, but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			for (int n = 0; n < _amt; n++)
			{
				bool bBorder = false;

				ImGui::PushID(n);
				{
					string name = ofToString(ofToString(n));

					// customize colors
					{
						// when selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							//const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonHovered];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// border with alpha
							//const ImVec4 c = style2.Colors[ImGuiCol_BorderShadow]; // TODO: get black from theme
							//const ImVec4 colorBorder = ImVec4(c.x, c.y, c.z, c.w * 1);
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							//const ImVec4 c = style2.Colors[ImGuiCol_TextDisabled]; 
							//const ImVec4 colorBorder = ImVec4(c.x, c.y, c.z, c.w * 0.15f);
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// border
						if (bBorder)
						{
							//uint32_t _time = ofGetElapsedTimeMillis();
							//float a = ofMap(_time % randomizeDuration, 0, randomizeDuration, 0.8, 0.4);
							ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
						}

						// draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							//load(n); // trig load preset
							cChanged = true;
						}

						// border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// customize colors
						ImGui::PopStyleColor(2);
					}

					float last_button_x2 = ImGui::GetItemRectMax().x;
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x; // Expected position if next button was on same line

					if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
				}
				ImGui::PopID();
			}

			//ImGui::TreePop();
		}

		ImGui::PopID();

		return cChanged;
	}

	//-

	// file selector

	// from https://gist.github.com/nariakiiwatani/dabf4cd2d04ad015bb6fabdedef7b2aa
	// buttons selector for files on a folder:
	// creates a button for each file showing each file names
	//--------------------------------------------------------------
	static bool SelectFile(const std::string &path, std::string &selected, /*int &index, */const std::vector<std::string> &ext = {}) {
		bool ret = false;

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetFontSize() * 2;

		if (ofFile(path).isDirectory()) {

			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			//flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			flagst |= ImGuiTreeNodeFlags_Framed;
			if (TreeNodeEx(ofFilePath::getBaseName(path).c_str(), flagst))

				//if (TreeNode(ofFilePath::getBaseName(path).c_str()))
			{
				ofDirectory dir;
				if (!ext.empty()) {
					dir.allowExt("");
					for (auto &&e : ext) {
						dir.allowExt(e);
					}
				}
				dir.listDir(path);
				for (auto &f : dir) {
					ret |= SelectFile(f.path(), selected, ext);
				}
				TreePop();
			}
		}
		else if (Button(ofFilePath::getFileName(path).c_str(), ImVec2(w, h))) {
			selected = path;
			ret = true;
		}
		return ret;
	}

	//TODO: add index
	//TODO: index not reflected
	// buttons selector for files on a folder:
	// creates a button for each file showing each file names
	//--------------------------------------------------------------
	static bool filesPicker(const std::string &path, std::string &selected, ofParameter<int>& _index, const std::vector<std::string> &ext = {}) {
		bool ret = false;

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetFontSize() * 2;

		int i = -1;

		if (ofFile(path).isDirectory()) {

			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			//flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			flagst |= ImGuiTreeNodeFlags_Framed;

			string _labelf = "FILES";
			//string _labelf = ofFilePath::getBaseName(path).c_str();

			//if (TreeNode(ofFilePath::getBaseName(path).c_str()))
			if (TreeNodeEx(_labelf.c_str(), flagst))
			{
				ofDirectory dir;
				if (!ext.empty()) {
					dir.allowExt("");
					for (auto &&e : ext) {
						dir.allowExt(e);
					}
				}
				dir.listDir(path);

				//int i = 0;
				//for (auto &f : dir) {
				//	string _n = ofToString(i);
				//	ret |= filesPicker(_n.c_str(), selected, ext);
				//	i++;
				//}

				for (auto &f : dir)
				{
					ret |= filesPicker(f.path(), selected, _index, ext);
				}

				TreePop();
			}
		}
		else // a file
		{
			i++;
			if (Button(ofFilePath::getFileName(path).c_str(), ImVec2(w, h))) {

				selected = path;
				ret = true;

				////TODO: index not reflected
				//if (i != -1) _index = i;
			}
		}
		return ret;
	}
};

//------------------------------------------------

// Taken from
// https://github.com/d3cod3/ofxVisualProgramming

namespace ofxImGuiSurfing
{
	//TODO:
	//not working

	//inline bool Pad2D(ImDrawList* drawList, float width, float height, float *_x, float *_y);

	//// Minimal implementation modified from: https://github.com/ocornut/imgui/issues/942
	//inline bool KnobFloat(ImDrawList* draw_list, float width, ImU32 color, const char* label, float* p_value, float v_min, float v_max, float v_step = 50.f);

	//namespace ofxImGuiSurfing
	//{
	using namespace ImGui;

	//--------------------------------------------------------------
	inline bool Pad2D(ImDrawList* drawList, float width, float height, float *_x, float *_y) {

		// visuals
		enum { LINE_WIDTH = 2 }; // handlers: small lines width
		enum { GRAB_RADIUS = 6 }; // handlers: circle radius

		ImGuiWindow* Window = ImGui::GetCurrentWindow();

		// prepare canvas
		const float dim = width > 0 ? width : ImGui::GetContentRegionAvailWidth();
		ImVec2 Canvas(dim, height);

		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
		ImGui::ItemSize(bb);

		// background grid
		if (Canvas.x >= 4) {
			for (int i = 0; i <= Canvas.x; i += static_cast<int>((Canvas.x / 4))) {
				drawList->AddLine(
					ImVec2(bb.Min.x + i, bb.Min.y),
					ImVec2(bb.Min.x + i, bb.Max.y - 1),
					IM_COL32(255, 255, 255, 20));
			}
		}

		if (Canvas.y >= 4) {
			for (int i = 0; i <= Canvas.y; i += static_cast<int>((Canvas.y / 4))) {
				drawList->AddLine(
					ImVec2(bb.Min.x, bb.Min.y + i),
					ImVec2(bb.Max.x - 1, bb.Min.y + i),
					IM_COL32(255, 255, 255, 20));
			}
		}

		drawList->AddLine(ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Min.y), ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Max.y - 1), ImGui::GetColorU32(ImGuiCol_TextDisabled), LINE_WIDTH);
		drawList->AddLine(ImVec2(bb.Min.x, bb.Min.y + (Canvas.y* *_y)), ImVec2(bb.Max.x - 1, bb.Min.y + (Canvas.y* *_y)), ImGui::GetColorU32(ImGuiCol_TextDisabled), LINE_WIDTH);


		// DRAG from circle
		bool changed = false;

		ImVec2 prevCursorPos = ImGui::GetCursorScreenPos();

		ImGui::SetCursorScreenPos(ImVec2(bb.Min.x + (Canvas.x* *_x) - 4, bb.Min.y + (Canvas.y* *_y) - 4));
		ImGui::InvisibleButton("circleGripBtn", ImVec2(8, 8));

		static bool isDraggingCircle = false;
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
			if (!isDraggingCircle) {
				isDraggingCircle = true;
			}

			ImVec2 _pos = ImClamp(ImVec2((ImGui::GetMousePos().x - bb.Min.x) / Canvas.x, (ImGui::GetMousePos().y - bb.Min.y) / Canvas.y), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));
			*_x = _pos.x;
			*_y = _pos.y;

			changed = true;
		}
		else if (ImGui::IsItemDeactivated()) {
			if (isDraggingCircle) isDraggingCircle = false;
		}

		drawList->AddCircleFilled(ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Min.y + (Canvas.y* *_y)), GRAB_RADIUS, IM_COL32(255, 255, 255, 245), 6);

		ImGui::SetCursorScreenPos(prevCursorPos);

		return changed;

	}

	////--------------------------------------------------------------
	//inline bool KnobFloat(ImDrawList* draw_list, float width, ImU32 color, const char* label, float* p_value, float v_min, float v_max, float v_step) {
	//	ImGuiIO& io = ImGui::GetIO();
	//	ImGuiStyle& style = ImGui::GetStyle();

	//	float gap = width / 6.0f;
	//	float radius_outer = width;
	//	float labelGap = width / 1.15f;
	//	ImVec2 pos = ImGui::GetCursorScreenPos();
	//	ImVec2 center = ImVec2(pos.x + radius_outer + gap, pos.y + labelGap + radius_outer);
	//	float line_height = ImGui::GetTextLineHeight();

	//	float ANGLE_MIN = 3.141592f * 0.75f;
	//	float ANGLE_MAX = 3.141592f * 2.25f;

	//	ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
	//	bool value_changed = false;
	//	bool is_active = ImGui::IsItemActive();
	//	bool is_hovered = ImGui::IsItemHovered();
	//	if (is_active && io.MouseDelta.x != 0.0f) {
	//		if (v_step <= 0) v_step = 50.f;
	//		float step = (v_max - v_min) / v_step;
	//		*p_value += io.MouseDelta.x * step;

	//		if (*p_value < v_min) *p_value = v_min;
	//		if (*p_value > v_max) *p_value = v_max;
	//		value_changed = true;
	//	}
	//	else if (is_hovered && (io.MouseDoubleClicked[0] || io.MouseClicked[2])) {
	//		*p_value = (v_max + v_min) * 0.5f;  // reset value
	//		value_changed = true;
	//	}

	//	float t = (*p_value - v_min) / (v_max - v_min);
	//	if (*p_value >= v_max) {
	//		t = 1.0f;
	//	}
	//	float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
	//	float angle_cos = cosf(angle), angle_sin = sinf(angle);
	//	float radius_inner = radius_outer * 0.40f;
	//	float radius_inner_medium = radius_outer * 0.82f;
	//	float line_width = width / 5.0f;

	//	draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(label).x) / 2.0f), pos.y + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);

	//	draw_list->AddCircleFilled(center, radius_outer, IM_COL32(28, 28, 28, 255), 32);

	//	draw_list->PathArcTo(center, radius_outer - 4, ANGLE_MIN, angle, 32);
	//	draw_list->PathArcTo(center, radius_inner_medium, angle, ANGLE_MIN, 32);
	//	draw_list->PathStroke(color, true, line_width);

	//	draw_list->AddCircleFilled(center, radius_inner, is_active ? ImGui::GetColorU32(ImGuiCol_FrameBgActive) : is_hovered ? ImGui::GetColorU32(ImGuiCol_FrameBgHovered) : IM_COL32(28, 28, 28, 255), 32);
	//	draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - line_width + 1), center.y + angle_sin * (radius_outer - line_width + 1)), color, line_width);

	//	char buffer[64];
	//	snprintf(buffer, sizeof buffer, "%.2f", *p_value);
	//	draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(buffer).x) / 2.0f), pos.y + labelGap + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), buffer);

	//	////tooltip
	//	//if (is_active || is_hovered)
	//	//{
	//	//	ImGui::SetNextWindowPos(ImVec2(pos.x + gap - style.WindowPadding.x, pos.y + labelGap + radius_outer));
	//	//	ImGui::BeginTooltip();
	//	//	ImGui::PushItemWidth(radius_outer * 2);
	//	//	ImGui::DragFloat("", p_value);
	//	//	ImGui::PopItemWidth();
	//	//	ImGui::EndTooltip();
	//	//}

	//	return value_changed;
	//}
	////}


	////--------------------------------------------------------------
	//inline bool getFileDialog(imgui_addons::ImGuiFileBrowser& fileDialog, bool show, std::string text, imgui_addons::ImGuiFileBrowser::DialogMode mode, std::string valid_types, std::string nameProposal = "", float retinaScale = 1.0f) {
	//	if (show) ImGui::OpenPopup(text.c_str());
	//	if (fileDialog.showFileDialog(text.c_str(), mode, ImVec2(700 * retinaScale, 380 * retinaScale), valid_types.c_str(), nameProposal)) {
	//		return true;
	//	}
	//	return false;
	//}

	//--------------------------------------------------------------
	static void HelpMarker(const char* desc) {
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--------------------------------------------------------------
	static void ObjectInfo(const char* desc, const char* url, float retinaScale = 1.0f) {
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::InvisibleButton("empty", ImVec2(224 * retinaScale, 1));  // fix widget width
		if (ImGui::CollapsingHeader("INFO", ImGuiTreeNodeFlags_None)) {
			ImGui::TextWrapped("%s", desc);
			ImGui::Spacing();
			if (ImGui::Button("Open Browser")) {
				ofLaunchBrowser(url);
			}
		}
	}

	//--------------------------------------------------------------
	inline void drawOFTexture(ofTexture* tex, float& _tw, float& _th, float& posX, float& posY, float& drawW, float& drawH) {
#define IMGUI_EX_NODE_HEADER_HEIGHT 20

		if (tex->isAllocated()) {
			if (tex->getWidth() / tex->getHeight() >= _tw / _th) {
				if (tex->getWidth() > tex->getHeight()) {   // horizontal texture
					drawW = _tw;
					drawH = (_tw / tex->getWidth())*tex->getHeight();
					posX = 0;
					posY = (_th - drawH) / 2.0f;
				}
				else { // vertical texture
					drawW = (tex->getWidth()*_th) / tex->getHeight();
					drawH = _th;
					posX = (_tw - drawW) / 2.0f;
					posY = 0;
				}
			}
			else { // always considered vertical texture
				drawW = (tex->getWidth()*_th) / tex->getHeight();
				drawH = _th;
				posX = (_tw - drawW) / 2.0f;
				posY = 0;
			}

			ImVec2 cursor_pos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(posX, posY + IMGUI_EX_NODE_HEADER_HEIGHT));

			ofxImGui::AddImage(*tex, ofVec2f(drawW, drawH));

			ImGui::SetCursorPos(cursor_pos);

		}
	}


	//--------------------------------------------------------------
	inline void drawTimecode(ImDrawList* drawList, int seconds, std::string pre = "", bool onDrawList = false, ImVec2 pos = ImVec2(0, 0), float fontScale = 1.0f) {
		int _hours = static_cast<int>(ceil(seconds) / 3600);
		int _minutes = static_cast<int>(ceil(seconds) / 60);
		int _seconds = static_cast<int>(round(seconds)) % 60;

		string _sh, _sm, _ss;

		if (_hours < 10) {
			_sh = "0" + ofToString(_hours);
		}
		else {
			_sh = ofToString(_hours);
		}

		if (_minutes < 10) {
			_sm = "0" + ofToString(_minutes);
		}
		else {
			_sm = ofToString(_minutes);
		}

		if (_seconds < 10) {
			_ss = "0" + ofToString(_seconds);
		}
		else {
			_ss = ofToString(_seconds);
		}

		if (onDrawList) {
			char temp[256];
			sprintf(temp, "%s %s:%s:%s", pre.c_str(), _sh.c_str(), _sm.c_str(), _ss.c_str());
			drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize()*fontScale, pos, IM_COL32_WHITE, temp, NULL, 0.0f);
		}
		else {
			ImGui::Text("%s %s:%s:%s", pre.c_str(), _sh.c_str(), _sm.c_str(), _ss.c_str());
		}
	}
};

//-

namespace ofxImGuiSurfing
{
	//bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f);

	////----

	////TODO:
	//// knob from https://github.com/yumataesu/ImGui_Widgets
	//// https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
	////example:
	////static float val = 0.0;
	////ofxImGui::Knob("value", &val, 0, 1); ImGui::SameLine();
	////ImGui::KnobNeedleTrail("value", &val, 0, 1);
	////--------------------------------------------------------------
	//static inline bool Knob(const char* label, float* value_p, float minv, float maxv) {
	//	ImGuiStyle& style = ImGui::GetStyle();
	//	//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
	//	//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
	//	//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);

	//	float sz = 36.0f;

	//	float line_height = ImGui::GetTextLineHeight();

	//	ImVec2 p = ImGui::GetCursorScreenPos();
	//	float radio = sz * 0.5f;
	//	ImVec2 center = ImVec2(p.x + radio, p.y + radio);
	//	float val1 = (value_p[0] - minv) / (maxv - minv);
	//	char textval[32];
	//	ImFormatString(textval, IM_ARRAYSIZE(textval), "%04.1f", value_p[0]);

	//	ImVec2 textpos = p;
	//	float gamma = M_PI / 4.0f;//0 value in knob
	//	float alpha = (M_PI - gamma)*val1*2.0f + gamma;

	//	float x2 = -sinf(alpha)*radio + center.x;
	//	float y2 = cosf(alpha)*radio + center.y;

	//	ImGui::InvisibleButton(label, ImVec2(sz, sz + line_height + style.ItemInnerSpacing.y));

	//	bool is_active = ImGui::IsItemActive();
	//	bool is_hovered = ImGui::IsItemHovered();
	//	bool touched = false;

	//	if (is_active) {
	//		touched = true;
	//		ImVec2 mp = ImGui::GetIO().MousePos;
	//		alpha = atan2f(mp.x - center.x, center.y - mp.y) + M_PI;
	//		//alpha = MAX(gamma, MIN(2.0f*M_PI - gamma, alpha));
	//		//alpha = ImMax(gamma, ImMin(2.0f*M_PI - gamma, alpha));
	//		float value = 0.5f*(alpha - gamma) / (M_PI - gamma);
	//		value_p[0] = value * (maxv - minv) + minv;
	//	}

	//	ImVec2 offset = ImVec2(0, 25);

	//	ImU32 col32 = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	//	ImU32 col32line = ImGui::GetColorU32(ImGuiCol_SliderGrabActive);
	//	ImU32 col32text = ImGui::GetColorU32(ImGuiCol_Text);
	//	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	//	draw_list->AddCircleFilled(center, radio, col32, 16);
	//	draw_list->AddLine(center, ImVec2(x2, y2), col32line, 3);
	//	draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y), col32text, textval);
	//	draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y + 20), col32text, label);

	//	//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
	//	//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
	//	//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);

	//	return touched;
	//}

	//-

	//https://gist.github.com/nariakiiwatani/dabf4cd2d04ad015bb6fabdedef7b2aa

	//namespace ofxImGuiSurfing
	//{
	//	static bool SelectFile(const std::string &path, std::string &selected, const std::vector<std::string> &ext = {}) {
	//		bool ret = false;
	//		if (ofFile(path).isDirectory()) {
	//			if (TreeNode(ofFilePath::getBaseName(path).c_str())) {
	//				ofDirectory dir;
	//				if (!ext.empty()) {
	//					dir.allowExt("");
	//					for (auto &&e : ext) {
	//						dir.allowExt(e);
	//					}
	//				}
	//				dir.listDir(path);
	//				for (auto &f : dir) {
	//					ret |= SelectFile(f.path(), selected, ext);
	//				}
	//				TreePop();
	//			}
	//		}
	//		else if (Button(ofFilePath::getFileName(path).c_str())) {
	//			selected = path;
	//			ret = true;
	//		}
	//		return ret;
	//	}
	//}

	//TODO:
	//BUG:
	//when drawing two plots both are sharing variables ?? so only drawing one
	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, ImVec2 v2 = ImVec2(100, 80.0f))
	{
		ImGui::PushID(1);

		static float min = parameter.getMin();
		static float max = parameter.getMax();
		static std::string name = parameter.getName();
		//ImGui::Text(name.c_str());

		static bool animate = true;

		// Fill an array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
		// and the sizeof() of your structure in the "stride" parameter.

		//static const size_t duration = 60 * 4;//fps * secs
		//static float values[duration] = {};
		static float values[120] = {};

		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (!animate || refresh_time == 0.0)
			refresh_time = ImGui::GetTime();
		while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
		{
			static float phase = 0.0f;
			values[values_offset] = parameter.get();
			//values[values_offset] = cosf(phase);

			values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
			phase += 0.10f * values_offset;
			refresh_time += 1.0f / 60.0f;
		}

		static bool bOverlayAvg = false;
		static char overlay[32] = "";
		if (bOverlayAvg)
		{
			float average = 0.0f;
			for (int n = 0; n < IM_ARRAYSIZE(values); n++)
				average += values[n];
			average /= (float)IM_ARRAYSIZE(values);
			sprintf(overlay, "avg %f", average);
		}

		//ImGui::PushID(1);
		//ImGui::PlotLines("Plot", values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);
		ImGui::PlotLines(name.c_str(), values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);

		//ImGui::PushID(1);
		ImGui::Checkbox("Animate", &animate);

		ImGui::PopID();
	}

	//----

	////TODO:
	////snap engine
	//auto snap = [=](float value, float snap_threshold) -> float {
	//	float modulo = std::fmodf(value, snap_threshold);
	//	float moduloRatio = std::fabsf(modulo) / snap_threshold;
	//	if (moduloRatio < 0.5f)
	//		value -= modulo;
	//	else if (moduloRatio > (1.f - 0.5f))
	//		value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
	//	return value;
	//};
	////ImGui::Begin(name.data());
	////if (ImGui::IsItemActive()) 
	//{
	//	auto p = ImGui::GetWindowPos();
	//	auto size = ImGui::GetWindowSize();

	//	float x = snap(p.x, 16.f);
	//	float y = snap(p.y, 16.f);
	//	float sizex = snap(size.x, 16.f);
	//	float sizey = snap(size.y, 16.f);
	//	ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
	//}
};

//-----

//TODO:
//extra widgets
//https://github.com/MacFurax/ofxImGui/blob/docking/libs/imgui/src/imgui_widgets.cpp

//namespace ofxImGuiSurfing
//{
//	//used by AddKnob
//	//--------------------------------------------------------------
//	inline bool KnobNeedleTrail(const char* label, float* p_value, float v_min, float v_max, float trailZero, float radius = 20, float incPrecision = 0.001)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		ImGuiStyle& style = ImGui::GetStyle();
//
//		ImVec2 pos = ImGui::GetCursorScreenPos(); // get top left pos of current widget
//		float line_height = ImGui::GetTextLineHeight();
//		float space_height = line_height * 0.1; // to add between top, label, knob, value and bottom
//		float space_width = radius * 0.1; // to add on left and right to diameter of knob
//		ImVec4 widgetRec = ImVec4(pos.x, pos.y, radius*2.0f + space_width * 2.0f, space_height*4.0f + radius * 2.0f + line_height * 2.0f);
//		ImVec2 labelLength = ImGui::CalcTextSize(label);
//
//		ImVec2 center = ImVec2(pos.x + space_width + radius, pos.y + space_height * 2 + line_height + radius);
//
//		ImDrawList* draw_list = ImGui::GetWindowDrawList();
//
//		float ANGLE_MIN = 3.141592f * 0.75f;
//		float ANGLE_MAX = 3.141592f * 2.25f;
//
//		ImGui::InvisibleButton(label, ImVec2(widgetRec.z, widgetRec.w));
//		bool value_changed = false;
//		bool is_active = ImGui::IsItemActive();
//		bool is_hovered = ImGui::IsItemHovered();
//		if (is_active && io.MouseDelta.x != 0.0f)
//		{
//			float step = (v_max - v_min) / incPrecision;
//			*p_value += io.MouseDelta.x * step;
//			if (*p_value < v_min) *p_value = v_min;
//			if (*p_value > v_max) *p_value = v_max;
//			value_changed = true;
//		}
//
//		float t = (*p_value - v_min) / (v_max - v_min);
//		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
//		float angle_cos = cosf(angle), angle_sin = sinf(angle);
//		float radius_inner = radius * 0.35f;
//
//		float refZeroTrailVal = (trailZero - v_min) / (v_max - v_min);
//		float refZeroTrailAngle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * refZeroTrailVal;
//
//
//		//draw label
//		float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
//		draw_list->AddText(ImVec2(texPos, pos.y + space_height), ImGui::GetColorU32(ImGuiCol_Text), label);
//		// draw knob
//		if (style.FrameBorderSize > 0.0f)
//		{
//			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize + 1.0f, ImGui::GetColorU32(ImGuiCol_BorderShadow), 32);
//			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize, ImGui::GetColorU32(ImGuiCol_Border), 32);
//		}
//		// draw outer knob
//		draw_list->AddCircleFilled(center, radius, ImGui::GetColorU32(ImGuiCol_FrameBg), 32);
//
//		// draw needle
//		/*draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
//			ImVec2(center.x + angle_cos * (radius-1.5f), center.y + angle_sin * (radius-1.5f)),
//			ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);*/
//
//		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
//			ImVec2(center.x + angle_cos * (radius - 1.5f), center.y + angle_sin * (radius - 1.5f)),
//			ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), 2.0f);
//
//		//ImGuiCol_SliderGrab
//
//
//
//		// draw needle trail
//		if (refZeroTrailAngle < angle)
//		{
//			draw_list->PathArcTo(center, radius - 4.5f, refZeroTrailAngle, angle, 2 + (4 * (angle - refZeroTrailAngle))); // draw needle trail
//		}
//		else {
//			draw_list->PathArcTo(center, radius - 4.5f, angle, refZeroTrailAngle, 2 + (4 * (refZeroTrailAngle - angle))); // draw needle trail
//		}
//
//		draw_list->PathStroke(ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), false, 6.0f);
//
//		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16); // draw inner knob
//		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
//		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
//
//		// draw value
//		char temp_buf[64];
//		sprintf(temp_buf, "%.2f", *p_value);
//		labelLength = ImGui::CalcTextSize(temp_buf);
//		texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
//
//		draw_list->AddText(ImVec2(texPos, pos.y + space_height * 3 + line_height + radius * 2), ImGui::GetColorU32(ImGuiCol_Text), temp_buf);
//
//		return value_changed;
//	}
//};//ImGui

//-----

namespace ofxImGuiSurfing
{
	////TODO:
	////knob

	////bool AddKnob(ofParameter<float>& parameter);
	////bool AddKnob(ofParameter<float>& parameter, float zeroRef);
	////bool AddKnob(std::string label, ofParameter<float>& parameter);
	////bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef);

	////--------------------------------------------------------------
	//inline bool AddKnob(ofParameter<float> parameter, float trailZero, float radius = 20, float incPrecision = 0.001)
	//{
	//	std::string name = parameter.getName();
	//	//string name = parameter.getName();

	//	//trailZero = trailZero;
	//	auto tmpRef = parameter.get();
	//	if (ofxImGuiSurfing::KnobNeedleTrail(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), trailZero, radius, incPrecision))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

	////inline bool AddKnob(ofParameter<float>& parameter, float zeroRef)
	////{
	////	string name = parameter.getName();
	////	auto tmpRef = parameter.get();
	////	if (ofxImGuiSurfing::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	////	{
	////		parameter.set(tmpRef);
	////		return true;
	////	}
	////	return false;
	////}

	////inline bool AddKnob(std::string label, ofParameter<float>& parameter)
	////{
	////	string name = parameter.getName();
	////	auto tmpRef = parameter.get();
	////	if (ofxImGuiSurfing::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
	////	{
	////		parameter.set(tmpRef);
	////		return true;
	////	}
	////	return false;
	////}

	////inline bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef)
	////{
	////	string name = parameter.getName();
	////	auto tmpRef = parameter.get();
	////	if (ofxImGuiSurfing::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	////	{
	////		parameter.set(tmpRef);
	////		return true;
	////	}
	////	return false;
	////}

//-----

	//--------------------------------------------------------------
	inline void AddVoidWidget()
	{
		float h = ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2;
		ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_Disabled);
		//ImGui::Dummy(ImVec2(0, 2 * ImGui::GetStyle().ItemSpacing.y + 2 * ImGui::GetStyle().ItemInnerSpacing.y)); // hide widget
	}

//-----

	//--------------------------------------------------------------
	inline void ProgressBar2(float valuePrc, float max = 1.0f)
	{
		const float _w100 = ImGui::GetContentRegionAvail().x;
		const float pad = 0;

		// draw progress bar
		float _prc;
		ImGuiStyle *style = &ImGui::GetStyle();
		ImVec4 color;

		//ImGui::PushID("prog");
		color = style->Colors[ImGuiCol_ButtonHovered];//we can force change this color on theme... only used here
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 1.0f) _prc = valuePrc;
		else _prc = ofMap(valuePrc, 0, max, 0.f, 1.0f);

		ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));

		ImGui::PopStyleColor();
		//ImGui::PopID();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<float> valuePrc, float max = -1.0f)
	{
		//allways starts on 0.0f but max can be 1.0f, 100..
		if (max == -1.0f) ofxImGuiSurfing::ProgressBar2(valuePrc.get(), valuePrc.getMax());
		else ofxImGuiSurfing::ProgressBar2(valuePrc.get(), 1.0f);
	}

	//--------------------------------------------------------------
	inline void ProgressBar2(int valuePrc, int max = 100)
	{
		float _w100 = ImGui::GetContentRegionAvail().x;
		float pad = 0;

		// draw progress bar
		float _prc;
		ImGuiStyle *style = &ImGui::GetStyle();
		ImVec4 color;

		//ImGui::PushID("prog");
		color = style->Colors[ImGuiCol_ButtonHovered];//we can force change this color on theme... only used here
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 100) _prc = valuePrc / 100.f;
		else _prc = ofMap(valuePrc, 0, max, 0.f, 1.0f);

		ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));
		ImGui::PopStyleColor();
		//ImGui::PopID();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<int> valuePrc, int max = -1)
	{
		//allways starts on 0.0f but max can be 1.0f, 100..
		if (max == -1) ProgressBar2(valuePrc.get(), valuePrc.getMax());
		else ProgressBar2(valuePrc.get(), max);
	}
};

//-----



//--

// Spin Input Widget - Int/Float/Double 
// with arrows selectors
// https://github.com/ocornut/imgui/issues/2649
// TODO: add ofParams

namespace ofxImGuiSurfing
{
	IMGUI_API bool SpinScaler(const char* label, ImGuiDataType data_type, void* data_ptr, const void* step, const void* step_fast, const char* format, ImGuiInputTextFlags flags);
	IMGUI_API bool SpinInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
	IMGUI_API bool SpinFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	IMGUI_API bool SpinDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
};

namespace ofxImGuiSurfing
{
	using namespace ImGui;

	//--------------------------------------------------------------
	/*static*/ inline bool ofxImGuiSurfing::SpinScaler(const char* label, ImGuiDataType data_type, void* data_ptr, const void* step, const void* step_fast, const char* format, ImGuiInputTextFlags flags)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		ImGuiStyle& style = g.Style;

		if (format == NULL)
			format = DataTypeGetInfo(data_type)->PrintFmt;

		char buf[64];
		DataTypeFormatString(buf, IM_ARRAYSIZE(buf), data_type, data_ptr, format);

		bool value_changed = false;
		if ((flags & (ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsScientific)) == 0)
			flags |= ImGuiInputTextFlags_CharsDecimal;
		flags |= ImGuiInputTextFlags_AutoSelectAll;
		flags |= ImGuiInputTextFlags_NoMarkEdited;  // We call MarkItemEdited() ourselve by comparing the actual data rather than the string.

		if (step != NULL)
		{
			const float button_size = GetFrameHeight();

			BeginGroup(); // The only purpose of the group here is to allow the caller to query item data e.g. IsItemActive()
			PushID(label);
			SetNextItemWidth(ImMax(1.0f, CalcItemWidth() - (button_size + style.ItemInnerSpacing.x) * 2));
			if (InputText("", buf, IM_ARRAYSIZE(buf), flags)) // PushId(label) + "" gives us the expected ID from outside point of view
				value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialTextA.Data, data_type, data_ptr, format);

			// Step buttons
			const ImVec2 backup_frame_padding = style.FramePadding;
			style.FramePadding.x = style.FramePadding.y;
			ImGuiButtonFlags button_flags = ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups;
			if (flags & ImGuiInputTextFlags_ReadOnly)
				button_flags |= ImGuiButtonFlags_Disabled;
			SameLine(0, style.ItemInnerSpacing.x);

			// start diffs
			float frame_height = GetFrameHeight();
			float arrow_size = std::floor(frame_height * .45f);
			float arrow_spacing = frame_height - 2.0f * arrow_size;

			BeginGroup();
			PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ g.Style.ItemSpacing.x, arrow_spacing });

			// save/change font size to draw arrow buttons correctly
			float org_font_size = GetDrawListSharedData()->FontSize;
			GetDrawListSharedData()->FontSize = arrow_size;

			if (ArrowButtonEx("+", ImGuiDir_Up, ImVec2(arrow_size, arrow_size), button_flags))
			{
				DataTypeApplyOp(data_type, '+', data_ptr, data_ptr, g.IO.KeyCtrl && step_fast ? step_fast : step);
				value_changed = true;
			}

			if (ArrowButtonEx("-", ImGuiDir_Down, ImVec2(arrow_size, arrow_size), button_flags))
			{
				DataTypeApplyOp(data_type, '-', data_ptr, data_ptr, g.IO.KeyCtrl && step_fast ? step_fast : step);
				value_changed = true;
			}

			// restore font size
			GetDrawListSharedData()->FontSize = org_font_size;

			PopStyleVar(1);
			EndGroup();
			// end diffs

			const char* label_end = FindRenderedTextEnd(label);
			if (label != label_end)
			{
				SameLine(0, style.ItemInnerSpacing.x);
				TextEx(label, label_end);
			}
			style.FramePadding = backup_frame_padding;

			PopID();
			EndGroup();
		}
		else
		{
			if (InputText(label, buf, IM_ARRAYSIZE(buf), flags))
				value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialTextA.Data, data_type, data_ptr, format);
		}
		if (value_changed)
			MarkItemEdited(window->DC.LastItemId);

		return value_changed;
	}

	//--------------------------------------------------------------
	/*static*/ inline bool ofxImGuiSurfing::SpinInt(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags flags)
	{
		// Hexadecimal input provided as a convenience but the flag name is awkward. Typically you'd use InputText() to parse your own data, if you want to handle prefixes.
		const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
		return SpinScaler(label, ImGuiDataType_S32, (void*)v, (void*)(step > 0 ? &step : NULL), (void*)(step_fast > 0 ? &step_fast : NULL), format, flags);
	}

	//--------------------------------------------------------------
	/*static*/ inline bool ofxImGuiSurfing::SpinFloat(const char* label, float* v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags)
	{
		flags |= ImGuiInputTextFlags_CharsScientific;
		return SpinScaler(label, ImGuiDataType_Float, (void*)v, (void*)(step > 0.0f ? &step : NULL), (void*)(step_fast > 0.0f ? &step_fast : NULL), format, flags);
	}

	//--------------------------------------------------------------
	/*static*/ inline bool ofxImGuiSurfing::SpinDouble(const char* label, double* v, double step, double step_fast, const char* format, ImGuiInputTextFlags flags)
	{
		flags |= ImGuiInputTextFlags_CharsScientific;
		return SpinScaler(label, ImGuiDataType_Double, (void*)v, (void*)(step > 0.0 ? &step : NULL), (void*)(step_fast > 0.0 ? &step_fast : NULL), format, flags);
	}
};
