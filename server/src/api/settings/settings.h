#pragma once
// The settings module's parts (api/settings/README.md), registered together by register_settings()
// (core/modules.h, defined in account.cpp). Port code, not guest behaviour.
namespace soa::server::settings {

void register_config();            // config.cpp: GetConfig, UpdateConfig, ResetConfig, the player load's ConfigInfoList
void register_account();           // account.cpp: Get/UpdateBirthYearMonth, ReadExpirationInfo, SendGuideInformation
void register_scenario_library();  // scenario_library.cpp: GetScenarioLibraryInfoList

}  // namespace soa::server::settings
