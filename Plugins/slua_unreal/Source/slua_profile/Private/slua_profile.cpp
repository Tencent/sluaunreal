// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "slua_profile.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "FileManager.h"
#include "Engine/GameEngine.h"

#define LOCTEXT_NAMESPACE "Fslua_profileModule"
static const FName slua_profileTabName("slua_profile");

void Fslua_profileModule::StartupModule()
{
	if (GIsEditor && !IsRunningCommandlet()) {
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(slua_profileTabName, FOnSpawnTab::CreateRaw(this, &Fslua_profileModule::OnSpawnPluginTab))
			.SetDisplayName(LOCTEXT("Flua_wrapperTabTitle", "slua Profiler"))
			.SetMenuType(ETabSpawnerMenuType::Hidden);
	}
}

void Fslua_profileModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(slua_profileTabName);
}

TSharedRef<class SDockTab> Fslua_profileModule::OnSpawnPluginTab(const FSpawnTabArgs & SpawnTabArgs)
{
	FText WidgetText = LOCTEXT("WindowWidgetText", "Add code to display profiler");

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()[
					SNew(STextBlock)
						.Text(WidgetText)
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fslua_profileModule, slua_profile)
