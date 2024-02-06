#include "LeftMenu.hpp"
#include "BottomMenu.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "tool.hpp"
#include <queue>
#include <string>

static void SceneTree();

// TODO: Make panel width adjust on runtime
int LeftMenu::width = 128;
Rectangle LeftMenu::rec{};

static Vector2 sDim{};

void LeftMenu::Resize(){
  sDim = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  rec = {0.0f, (float)TopMenu::width, (float)width,sDim.y-TopMenu::width-BottomMenu::width};
}

void LeftMenu::Draw() {
  raygui::GuiPanel(rec, nullptr);
  SceneTree();
}

static int countSceneItems(){
  int out = 0;
  std::queue<Node*> queue{};
  queue.push(Scene::getRoot());
  for(Node* n=queue.front(); !queue.empty(); n=queue.front()){
      queue.pop();
      out++;
      if(n->collapsed)
          continue;
      auto& childs = n->getChildren();
      for(auto& child: childs)
          queue.push(child.get());
      out += n->getGuis().size();
  }
  return out;
}
static std::string createIndent(int indent){
  std::string out = "";
  for(int i=0; i<indent; i++){
    out += "  ";
  }
  return out;
}
static int calcRank(Node* node){
  int out = 0;
  for(Node* n = node; !n->isOrphan() ; n = n->getParent()){
    out++;
  }
  return out;
}

static void handleChoosen(int choice){
  if(choice == -1)
    return;
  int index = 0;
  bool isGui = false;
  void* res = nullptr;
  std::vector<Node*> stack{};
  stack.push_back(Scene::getRoot());
  bool found = false;
  for(Node* n=stack.front(); !stack.empty(); n=stack.back()){
      stack.pop_back();
      if(index == choice){
        res = n;
        break;
      }
      index++;
      if(n->collapsed)
          continue;
      auto& childs = n->getChildren();
      for(auto& child: childs)
          stack.push_back(child.get());
      auto& guis = n->getGuis();
      for(auto& gui: guis){
        if(index == choice){
          res = gui.get();
          isGui =true;
          found = true;
          break;
        }
        index++;
      }
      if(found) break;
  }

  bool toggle = (static_cast<Node*>(res) == Tool::selectNODE) & !Tool::selectedGui;
  Tool::selectGUI.clear();
  Tool::selectNODE = nullptr;
  if(isGui){
    Tool::selectedSingle = true;
    Tool::selectedGui = true;
    Tool::selectGUI.insert(static_cast<GUI*>(res));
    return;
  }
  // is node
  Tool::selectedSingle = true;
  Tool::selectedGui = false;
  Tool::selectNODE = static_cast<Node*>(res);
  if(toggle)
    Tool::selectNODE->collapsed ^= true;
}

static void fillData(std::string *arr, bool *active, int *ranks){
  int index = 0;
  std::vector<Node*> stack{};
  stack.push_back(Scene::getRoot());
  for(Node* n=stack.front(); !stack.empty(); n=stack.back()){
      int rank = calcRank(n);
      stack.pop_back();
      active[index] = Tool::selectedSingle & !Tool::selectedGui & (Tool::selectNODE == n);
      ranks[index] = rank;
      arr[index] = "#11" + std::to_string(6 - n->collapsed) + "#" +  n->name;
      index++;
      if(n->collapsed)
          continue;
      auto& childs = n->getChildren();
      for(auto& child: childs)
          stack.push_back(child.get());
      auto& guis = n->getGuis();
      rank+= 2;
      for(auto& gui: guis){
        if(Tool::selectedGui)
          active[index] = (Tool::selectGUI.find(gui.get()) != Tool::selectGUI.end());
        ranks[index] = rank;
        arr[index++] = gui->getLabel();
      }
  }
}

static void SceneTree(){
  static float margin = 2;
  static Vector2 scroll = {};
  Rectangle sRec = { 0 };
  Rectangle bounds = LeftMenu::rec;
  float width = bounds.width;
  float font = raygui::getFontSize();
  Vector2 itemDim{width - 16, font*1.2f};
  int itemCnt = countSceneItems();

  Rectangle content{
    bounds.x, bounds.y + 24,
    width - 8, (itemDim.y+margin)*itemCnt
  };

  Rectangle treeView[itemCnt];

  raygui::GuiScrollPanel(bounds, "#173#Scene Explorer",
      content,
      &scroll, &sRec);

  Vector2 fpos = {content.x + scroll.x + margin ,content.y + scroll.y};
  for(int i = 0; i < itemCnt; i++){
    treeView[i] = {fpos.x, fpos.y+(itemDim.y+margin)*i, itemDim.x,itemDim.y};
  }
  std::string labels[itemCnt];
  bool actives[itemCnt];
  int ranks[itemCnt];
  fillData(labels,actives, ranks);
  // labels[0] = "Root";

  bool locked = raygui::GuiIsLocked();
  if(!CheckCollisionPointRec(GetMousePosition(), sRec))
    raygui::GuiLock();

  int choosen = -1;

  BeginScissorMode(sRec.x, sRec.y, sRec.width, sRec.height);
  {
    raygui::GuiSetStyle(raygui::TOGGLE, raygui::TEXT_ALIGNMENT,raygui::TEXT_ALIGN_LEFT);
    for (int i = 0; i < itemCnt; i++){
      bool active = actives[i];
      raygui::GuiToggleRanked(treeView[i], labels[i].c_str(),&active,ranks[i]);
      if(active ^ actives[i])
        choosen = i;
    }
    raygui::GuiSetStyle(raygui::TOGGLE, raygui::TEXT_ALIGNMENT,raygui::TEXT_ALIGN_CENTER);
  }
  EndScissorMode();

  //TODO: toggle selection based on gui click
  if(choosen != -1)
    handleChoosen(choosen);

  if(!locked)
    raygui::GuiUnlock();
}