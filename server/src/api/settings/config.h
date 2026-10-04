#pragma once
// The player's options (設定 > その他設定 / バトル設定; api/settings/config.cpp). Port code, not guest
// behaviour. Rules: docs/server-rules.md#settings.
#include <string>

#include "soaserver/ext.h"

namespace soa::server::settings {

// The client looks an option up by its master_config id_label: CUIUtility::IsConfigListCheck
// (@01eea65c) compares CHash32(label) with each ConfigInfo's master_config_id (b), so a label names
// the same master_config row as its id (a: master_config.id = CHash32(id_label) for every row).
//   一時保管庫設定: CUIUtility::IsOneTimeStorageEnable (@01eea5f8), その他設定's first box (b); the
//   screen's text: on, equipment drawn from the gacha goes to the one-time storage instead of the
//   equipment slots (オンにするとガチャから入手した装備アイテムを装備所持枠ではなく、一時保管庫に送ります).
constexpr const char* kOneTimeStorage = "is_one_time_storage";
//   ガチャ以外で入手した装備アイテムを一時保管庫に送る: CUIUtility::IsOneTimeStorageExceptGachaEnable
//   (@01eea8e0), その他設定's 3_gacha_souko box (b); on, equipment obtained other than from the gacha
//   goes there (オンにするとガチャ以外で装備アイテムを入手した時に…一時保管庫に送ります).
constexpr const char* kOneTimeStorageExceptGacha = "is_one_time_storage_except_gacha";

// The option's value: the player's (UpdateConfig, the table `config`), else the master's default
// (master_config.value); "" for an id master_config doesn't have.
std::string config_value(ext::Ctx& ctx, u32 master_config_id);
// Whether the option is on: its value is exactly "true", as IsConfigListCheck reads it (b: a
// 4-byte string equal to "true"). An option master_config doesn't have is off.
bool config_on(ext::Ctx& ctx, u32 master_config_id);
// The same by id_label (kOneTimeStorage, ...): the id is CHash32(label).
bool config_on(ext::Ctx& ctx, const char* id_label);

}  // namespace soa::server::settings
