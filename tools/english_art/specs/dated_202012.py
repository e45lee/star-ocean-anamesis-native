"""Older banners by date, newest first (the user, 2026-10-07): the 2020-12-24 week's banners, as title
bands (inpaint + shade + English) over the dense lettering; the art's small name captions stay."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
from gacha_banners import S as GS, erase_first  # noqa: E402
S = dict(GS)
S["omake"] = {"size": 11, "bold": 1, "fill": "#ffffff", "clear": "inpaint", "align": "left"}
TAG = {"ガチャ": "Draws", "イベント": "Event", "キャンペーン": "Campaign"}
def tag(jp):
    return L(jp, TAG[jp], [73, 14, 80, 15], "tag", [72, 15, 66 if jp == "キャンペーン" else 52, 13])
def w(name, note, labels):
    write(name, note, S, erase_first(labels))
w("20201224_chara_001", "The rerun 2017 Christmas step-up gacha's banner.", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
    L("★復刻2017★クリスマス 10連10ステップ目 PUいずれか1体確定ガチャ", "Rerun 2017 Christmas\nStep 10: 1 Pick-up\nguaranteed (10-chain)",
      [66, 40, 150, 72], "gold", [60, 34, 160, 80], size=18),
    L("ステップ10はPUいずれか1体確定!", "Step 10: 1 pick-up guaranteed!", [270, 98, 186, 18], "bar_r", [270, 96, 186, 20], clear="shade", clear_color="#200400c0")])
w("20201224_chara_002", "Evelysse's birthday pick-up gacha's banner (Evelysse: glossary).", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 159 - 128, 50, 11], "omake", [57, 31, 48, 11]),
    L("イヴリーシュ誕生日記念 ピックアップキャラガチャ 10連でピックアップいずれか1体確定!", "Evelysse's Birthday\nPick-up Character Draws\n10-chain: 1 pick-up guaranteed!",
      [262, 26, 194, 90], "gold_r", [256, 22, 202, 98], size=18)])
w("20201224_chara_003", "The weekend-limited character pick-up gacha's banner.", [
    tag("ガチャ"),
    L("週末限定 キャラクターピックアップ ピックアップは期間限定キャラのみ!", "Weekend Limited\nCharacter Pick-up\nLimited characters only!",
      [272, 38, 184, 78], "gold_r", [266, 6, 192, 112], size=18)])
w("20201224_chara_004", "Ricardo's awakening banner (Ricardo: glossary).", [
    L("リカルド覚醒", "Ricardo\nAwakened", [66, 26, 230, 82], "blue", [62, 28, 230, 80], size=30, align="left")])
w("20201224_event_001", "The Wadrum, Holy Land of Oblivion event's banner (hour 6; Misery 2 / 3: Global's 滅級 / 絶級).", [
    tag("イベント"),
    L("忘却の聖地 ウドラム", "Wadrum, Holy Land\nof Oblivion", [60, 32, 220, 58], "blue", [58, 32, 190, 64], size=22, align="left"),
    L("第6刻", "Hour 6", [350, 60, 100, 30], "blue", [356, 60, 90, 30], size=22, align="right"),
    L("滅級・絶級追加", "Misery 2 & 3 added", [86, 96, 170, 18], "blue_s", [96, 96, 116, 18], clear="inpaint", size=13)])
w("20201224_event_002", "The Feast of Champions event's banner.", [
    tag("イベント"),
    L("覇者の祭宴", "Feast of\nChampions", [326, 28, 130, 86], "gold_r", [320, 28, 136, 86], size=24)])
w("20201224_weapon_001", "A pick-up weapon gacha's banner (3 slots, with a bonus).", [
    tag("ガチャ"),
    L("ピックアップ武器ガチャ", "Pick-up Weapon Draws", [170, 15, 170, 14], "blue_s", [176, 15, 156, 14], clear="inpaint", size=13),
    L("3スロット", "3 Slots", [368, 15, 40, 13], "tag", [368, 15, 40, 13], clear="inpaint", size=10),
    L("10連で★5新武器1本確定!!", "10-chain: 1 new\n★5 weapon guaranteed!!", [250, 52, 206, 64], "gold_r", [248, 44, 208, 72], size=20),
    L("おまけ付き", "Bonus", [410, 27, 46, 11], "omake", [410, 27, 46, 11])])
w("20201224_campaign_001", "The 2020-2021 New Year campaign's banner.", [
    tag("キャンペーン"),
    L("年末年始 2020-2021 キャンペーン", "New Year\n2020-2021\nCampaign", [228, 30, 196, 86], "gold", [222, 2, 208, 120], size=22)])
w("20201224_campaign_002", "The item shop's New Year weapon sets campaign banner.", [
    tag("キャンペーン"),
    L("アイテムショップで 年末年始武器強化セット 期間限定追加", "Limited-time New Year\nWeapon Enhancement Sets\nin the Item Shop",
      [250, 32, 206, 84], "gold_r", [246, 4, 210, 116], size=17)])
