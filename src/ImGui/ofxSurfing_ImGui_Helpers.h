#pragma once

#include "ofxImGui.h"

// TODO:
// TESTING TOGGLE TYPES
#include "ofxSurfing_ImGui_WidgetsTypes.h"

/*

	NOTE from moebiusSurfing:
	This is a cleaner modified version of ImHelpers.h from the original ofxImGui with these modifications:
	- Deprecated GetUniqueName engine. Now using ImGui::PushId(1) | ImGui::PopID() for each parameter widget.
	- Deprecated all old window/settings/tree management. Now much simpler and closer to raw ImGui.

*/


//#include "ofGLBaseTypes.h"
//#include "ofParameter.h"
//#include "ofRectangle.h"
//#include "ofTexture.h"
//#include "ofGLBaseTypes.h"
//#include "imgui.h"
//#include <stack> // Needed for Arch Linux

//static const int kImGuiMargin2 = 10;

// namespace ofxImGui
namespace ofxSurfing
{
	//// TODO:
	//// TESTING TOGGLE TYPES
	//class SurfingImGuiHelpers {
	//public:
	//	SurfingImGuiHelpers() {};
	//	~SurfingImGuiHelpers() {};

	//--

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	//struct WindowOpen
	//{
	//	std::stack<std::vector<std::string>> usedNames;
	//	std::shared_ptr<ofParameter<bool>> parameter;
	//	bool value;
	//};

	//struct Settings
	//{
	//	Settings();
	//	ofVec2f windowPos;
	//	ofVec2f windowSize;
	//	bool lockPosition;
	//	
	//	bool mouseOverGui;
	//	bool windowBlock;
	//	int treeLevel;
	//	ofRectangle totalBounds;
	//	ofRectangle screenBounds;
	//};

	//static WindowOpen windowOpen;

	//bool IsMouseOverGui();

	//const char * GetUniqueName(ofAbstractParameter& parameter);
	//const char * GetUniqueName(const std::string& candidate);

	//void SetNextWindow(Settings& settings);
	//bool BeginWindow(ofParameter<bool>& parameter, Settings& settings, bool collapse = true);
	//bool BeginWindow(const std::string& name, Settings& settings, bool collapse = true, bool * open = nullptr);
	//bool BeginWindow(const std::string& name, Settings& settings, ImGuiWindowFlags flags, bool * open = nullptr);
	//void EndWindow(Settings& settings);

	//bool BeginTree(ofAbstractParameter& parameter, Settings& settings);
	//bool BeginTree(const std::string& name, Settings& settings);
	//void EndTree(Settings& settings);

	//void AddGroup(ofParameterGroup& group, Settings& settings);
	//void AddGroup(ofParameterGroup& group, Settings& settings, ImGuiTreeNodeFlags flags);//TODO: settings + flags

	//NEW: add flags and clean all the old settings
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& parameter);
	bool AddParameter(ofParameter<glm::ivec3>& parameter);
	bool AddParameter(ofParameter<glm::ivec4>& parameter);

	bool AddParameter(ofParameter<glm::vec2>& parameter);
	bool AddParameter(ofParameter<glm::vec3>& parameter);
	bool AddParameter(ofParameter<glm::vec4>& parameter);
#endif

	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);

	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false);

	bool AddParameter(ofParameter<void>& parameter, float width = 0);

	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter);

	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label = true);

	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns = 1);
	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels);
	bool AddStepper(ofParameter<int>& parameter, int step = 1, int stepFast = 100);

	bool AddSlider(ofParameter<float>& parameter, const char* format = "%.3f", float power = 1.0f);

	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed = 1);
	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed = 0.01f);
#if OF_VERSION_MINOR >= 10
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed = 0.01f);
#endif

#if OF_VERSION_MINOR >= 10
	bool AddValues(const std::string& name, std::vector<glm::ivec2>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec3>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec4>& values, int minValue = 0, int maxValue = 0);

	bool AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue = 0, float maxValue = 0);
#endif

	bool AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue = 0, float maxValue = 0);

	template<typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue);

	void AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size);
	void AddImage(const ofTexture& texture, const ofVec2f& size);
#if OF_VERSION_MINOR >= 10
	void AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size);
	void AddImage(const ofTexture& texture, const glm::vec2& size);
#endif

}//namespace ofxSurfing


static ImTextureID GetImTextureID2(const ofTexture& texture)
{
	return (ImTextureID)(uintptr_t)texture.texData.textureID;
}

static ImTextureID GetImTextureID2(const ofBaseHasTexture& hasTexture)
{
	return GetImTextureID2(hasTexture.getTexture());
}

static ImTextureID GetImTextureID2(GLuint glID)
{
	return (ImTextureID)(uintptr_t)glID;
}


//--------------------------------------------------------------
template<typename ParameterType>
bool ofxSurfing::AddParameter(ofParameter<ParameterType>& parameter)
{
	auto tmpRef = parameter.get();
	const auto& info = typeid(ParameterType);

	if (info == typeid(float))
	{
		ImGui::PushID(1);
		if (ImGui::SliderFloat(parameter.getName().c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);
			ImGui::PopID();
			return true;
		}
		ImGui::PopID();
		return false;
	}

	if (info == typeid(int))
	{
		ImGui::PushID(1);
		if (ImGui::SliderInt(parameter.getName().c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);
			ImGui::PopID();
			return true;
		}
		ImGui::PopID();
		return false;
	}

	if (info == typeid(bool))
	{
		ImGui::PushID(1);
		if (ImGui::Checkbox(parameter.getName().c_str(), (bool *)&tmpRef))
		{
			parameter.set(tmpRef);
			ImGui::PopID();
			return true;
		}
		ImGui::PopID();
		return false;
	}

	//// TODO:
	//// TESTING TOGGLE TYPES
	//if (info == typeid(bool))
	//{

	//}

	ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	return false;
}

//--------------------------------------------------------------
template<typename ParameterType>
bool ofxSurfing::AddText(ofParameter<ParameterType>& parameter, bool label)
{
	ImGui::PushID(1);
	if (label)
	{
		ImGui::LabelText(parameter.getName().c_str(), ofToString(parameter.get()).c_str());
	}
	else
	{
		ImGui::Text(ofToString(parameter.get()).c_str());
	}
	ImGui::PopID();

	return true;
}

//--------------------------------------------------------------
template<typename DataType>
bool ofxSurfing::AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue)
{
	auto result = false;
	const auto& info = typeid(DataType);
	for (int i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		if (info == typeid(float))
		{
			ImGui::PopID();
			result |= ImGui::SliderFloat(GetUniqueName(iname), *values[i], minValue, maxValue);
			ImGui::PopID();
		}
		else if (info == typeid(int))
		{
			ImGui::PopID();
			result |= ImGui::SliderInt(GetUniqueName(iname), *values[i], minValue, maxValue);
			ImGui::PopID();
		}
		else if (info == typeid(bool))
		{
			ImGui::PopID();
			result |= ImGui::Checkbox(GetUniqueName(iname), *values[i]);
			ImGui::PopID();
		}
		else
		{
			ofLogWarning(__FUNCTIONS__) << "Could not create GUI element for type " << info.name();
			return false;
		}
	}
	return result;

}

//}; // class

