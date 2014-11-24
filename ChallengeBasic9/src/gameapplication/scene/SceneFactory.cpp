#include "SceneFactory.h"
#include "title\Title.h"
#include "stage\Stage.h"

CSceneFactory::CSceneFactory(std::shared_ptr<AppEnv>app_env)
{
	m_scene_create_list.emplace(CScene::Type::TITLE, [app_env]{return std::make_unique<CTitle>(app_env); });
	m_scene_create_list.emplace(CScene::Type::STAGE, [app_env]{return std::make_unique<CStage>(app_env); });
}