# Restore inventory: events, Sphere 211, tower and banners in the available assets

**Generated snapshot — do not edit by hand, and do not hard-code anything from it.** The game and the local server decide at runtime what is usable; this file only reports what the current asset sources hold. Regenerate after downloading more assets:

```
.venv/bin/python tools/event_coverage.py --db data/basmaster-3.7.0.sqlite3 --src work/SOA-3.7.0-canonical-data.zip --src apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk --notes docs/event-notes.tsv --md docs/restore-inventory.md --quiet
```

Sources scanned (logical files): `work/SOA-3.7.0-canonical-data.zip` (26046), `apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk` (618)

Classes: **FULL** = maps, enemy models, talk scripts, background and banner all present; **PLAYABLE** = every battle map and enemy model present, but some talk scripts / background / banner missing (battles work, story scenes or art don't); **BROKEN** = a battle map or enemy model is missing; **NO-MISSIONS** = the area has no missions. Not checked: TalkScene .csf, movies, voices, motions, item icons.

## Events

168 event areas: FULL 38, PLAYABLE 83, BROKEN 35, NO-MISSIONS 12.

### FULL (38)

| event | name | kind | terms (first..last) | missions | scripts | maps | enemies | bg | banner | missing |
|---|---|---|---|---|---|---|---|---|---|---|
| `event_evo_blue` | 青の進化素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_evo_green` | 緑の進化素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_evo_purple` | 紫の進化素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_evo_red` | 赤の進化素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_evo_yellow` | 黄の進化素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_money` | 売却素材ミッション | daily+weekly | 0 (..) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_wep_exp` | ハンマーミッション | daily | 16 (2017-01-04..2020-05-21) | 1 | 0/0 | 1/1 | 2/2 | yes | yes |  |
| `event_exp_all` | 虹の経験値素材ミッション | daily+weekly | 93 (2017-03-16..2021-06-24) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_evo_all` | 虹の進化素材ミッション | daily+weekly | 89 (2017-05-31..2021-06-24) | 3 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_acc_exp` | スレッドミッション | daily | 15 (2017-07-27..2020-05-21) | 1 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_sed_exp` | シードミッション | daily | 1 (2017-09-21..2030-12-31) | 1 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_spring_89` | 温泉イベント | worldboss+bighunt+story | 1 (2020-02-27..2020-03-19) | 24 | 9/9 | 3/3 | 7/7 | yes | yes |  |
| `event_EP3CP1` | EP3CP1イベントミッション | type3 | 3 (2020-04-30..2021-06-17) | 7 | 0/0 | 1/1 | 3/3 | yes | yes |  |
| `event_Memory_01` | 忘却の聖地ワドラム第1弾 | story | 2 (2020-05-14..2021-06-17) | 11 | 6/6 | 3/3 | 7/7 | yes | yes |  |
| `event_kimono_91` | 着物鬼イベント | story | 2 (2020-05-28..2021-06-17) | 15 | 7/7 | 3/3 | 6/6 | yes | yes |  |
| `event_Memory_02` | 忘却の聖地ワドラム第2弾 | story | 2 (2020-06-11..2021-06-17) | 9 | 4/4 | 2/2 | 4/4 | yes | yes |  |
| `event_EP3CP2` | EP3CP2イベントミッション | type3 | 3 (2020-06-25..2021-06-17) | 7 | 0/0 | 1/1 | 2/2 | yes | yes |  |
| `event_sww2020_93` | 水着イベント2020 | story | 2 (2020-07-30..2021-06-17) | 26 | 9/9 | 3/3 | 20/20 | yes | yes |  |
| `event_EP3CP3` | EP3CP3イベントミッション | type3 | 2 (2020-08-27..2021-06-17) | 7 | 0/0 | 1/1 | 2/2 | yes | yes |  |
| `event_Memory_03` | 忘却の聖地ワドラム第3弾 | story | 2 (2020-09-10..2021-06-17) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_Memory_04` | 忘却の聖地ワドラム第4弾 | story | 2 (2020-10-08..2021-06-17) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_EP3CP4` | EP3CP4イベントミッション | type3 | 2 (2020-10-22..2021-06-17) | 7 | 0/0 | 1/1 | 4/4 | yes | yes |  |
| `event_Memory_05` | 忘却の聖地ワドラム第5弾 | story | 2 (2020-11-12..2021-06-17) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_4year_95` | 4周年イベント | story | 3 (2020-11-26..2021-06-17) | 16 | 7/7 | 8/8 | 7/7 | yes | yes |  |
| `event_Memory_06` | 忘却の聖地ワドラム第6弾 | story | 2 (2020-12-17..2021-06-17) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_2020_max_01` | 覇級祭り | battle | 1 (2020-12-28..2020-12-31) | 1 | 0/0 | 1/1 | 1/1 | yes | yes |  |
| `event_2020_max_02` | 覇級祭り | battle | 1 (2020-12-31..2021-01-03) | 1 | 0/0 | 1/1 | 1/1 | yes | yes |  |
| `event_newyear_87` | 2020正月イベント | story | 2 (2021-01-01..2021-06-17) | 16 | 8/8 | 3/3 | 5/5 | yes | yes |  |
| `event_newyear_88` | 正月イベント2021 | story | 2 (2021-01-01..2021-06-24) | 15 | 7/7 | 2/2 | 8/8 | yes | yes |  |
| `event_2020_max_03` | 覇級祭り | battle | 1 (2021-01-03..2021-01-06) | 1 | 0/0 | 1/1 | 1/1 | yes | yes |  |
| `event_2020_max_04` | 覇級祭り | battle | 1 (2021-01-06..2021-01-07) | 1 | 0/0 | 1/1 | 1/1 | yes | yes |  |
| `event_Memory_07` | 忘却の聖地ワドラム第7弾 | story | 2 (2021-01-14..2021-06-24) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_EP3CP5` | EP3CP5イベントミッション | type3 | 2 (2021-01-28..2021-06-24) | 7 | 0/0 | 1/1 | 2/2 | yes | yes |  |
| `event_Memory_08` | 忘却の聖地ワドラム第8弾 | story | 2 (2021-02-10..2021-06-24) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_EP3CP6` | EP3CP6イベントミッション | type3 | 2 (2021-02-25..2021-06-24) | 7 | 0/0 | 1/1 | 2/2 | yes | yes |  |
| `event_Memory_09` | 忘却の聖地ワドラム第9弾 | story | 2 (2021-03-11..2021-06-24) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |
| `event_idol4_89` | アイドル第四弾 | story | 2 (2021-03-25..2021-06-24) | 15 | 7/7 | 4/4 | 7/7 | yes | yes |  |
| `event_Memory_10` | 忘却の聖地ワドラム第10弾 | story | 2 (2021-04-08..2021-06-24) | 9 | 4/4 | 3/3 | 4/4 | yes | yes |  |

### PLAYABLE (83)

| event | name | kind | terms (first..last) | missions | scripts | maps | enemies | bg | banner | missing |
|---|---|---|---|---|---|---|---|---|---|---|
| `event_Sphere211_01` | 覇級イベント | battle | 0 (..) | 14 | 0/0 | 14/14 | 15/15 | – | **no** | banner banner_event_so1_100 |
| `event_kororin2018` | コロリンピック | type3 | 0 (..) | 4 | 0/0 | 4/4 | 4/4 | – | **no** | banner 20181129_event_004 |
| `event_ticket` | チケットミッション | daily | 1 (2016-01-01..2017-10-26) | 36 | 0/0 | 12/12 | 18/18 | **no** | yes | bg banner_ticket_event_001 |
| `event_so1_01` | ＳＯ１イベント（ゲレル） | story | 12 (2016-12-01..2020-11-26) | 7 | 1/3 | 4/4 | 5/5 | yes | yes |  |
| `event_so1_02` | ＳＯ１イベント（ジエ・リヴォース） | story | 13 (2016-12-22..2021-01-07) | 7 | 1/3 | 1/1 | 1/1 | yes | yes |  |
| `event_wel_04_03` | 聖夜の贈り物大作戦（３） | story | 2 (2016-12-22..2021-05-06) | 3 | 1/4 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_003; banner banner_event_chr_001 |
| `event_new_01` | 大そうじの心得 | story | 1 (2016-12-28..2017-01-12) | 1 | 1/2 | 0/0 | 0/0 | **no** | – | bg banner_event_newyear_001 |
| `event_new_02` | ハッピーニューイヤー | story | 1 (2017-01-01..2017-01-12) | 1 | 1/2 | 0/0 | 0/0 | **no** | – | bg banner_event_newyear_002 |
| `event_fro_04` | フロストツリー討伐 | battle | 88 (2017-01-19..2019-04-25) | 2 | 0/0 | 1/1 | 3/3 | **no** | **no** | bg banner_enemy_event_001; banner banner_enemy_event_001 |
| `event_mem_03` | 慰霊祭（３） | story | 2 (2017-01-19..2021-05-06) | 3 | 1/4 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_006; banner banner_event_chr_004 |
| `event_bat_05` | ＳＯ２闘技場イベント | story | 13 (2017-02-16..2021-01-14) | 7 | 1/3 | 1/1 | 10/10 | yes | yes |  |
| `event_cry_07` | クリスタルガーディアン討伐 | battle | 59 (2017-02-16..2018-06-28) | 2 | 0/0 | 1/1 | 3/3 | **no** | **no** | bg banner_enemy_event_002; banner banner_enemy_event_002 |
| `event_val_03` | チョコレート・パニック（３） | story | 2 (2017-02-16..2021-05-06) | 3 | 1/4 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_009; banner banner_event_chr_007 |
| `event_mic_06` | ＳＯ２ミカエル降臨イベント | story | 12 (2017-02-23..2021-01-28) | 8 | 1/3 | 1/1 | 1/1 | **no** | **no** | bg banner_event_so2_002; banner banner_event_so2_002 |
| `event_spo_08` | ＳＯ３エクスキューショナー襲来 | story | 13 (2017-03-09..2021-03-11) | 7 | 1/3 | 2/2 | 3/3 | **no** | **no** | bg banner_event_so3_001; banner banner_event_so3_001 |
| `event_mik_10` | 女ゴコロとひなあられ（３） | story | 2 (2017-03-16..2021-05-06) | 3 | 1/4 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_012; banner banner_event_chr_010 |
| `event_exp_purple` | 紫の経験値素材ミッション | daily+weekly | 38 (2017-03-23..2021-04-23) | 3 | 0/0 | 1/1 | 3/3 | **no** | yes | bg banner_roleexCas_002 |
| `event_exp_red` | 赤の経験値素材ミッション | daily+weekly | 75 (2017-03-23..2021-04-23) | 3 | 0/0 | 1/1 | 3/3 | **no** | yes | bg banner_roleexAtk_002 |
| `event_luc_13` | SO3ルシファー降臨 | story | 13 (2017-03-23..2021-03-18) | 8 | 1/3 | 1/1 | 1/1 | **no** | **no** | bg banner_event_so3_002; banner banner_event_so3_002 |
| `event_apr_12` | エイプリルフール | story | 1 (2017-04-01..2017-04-01) | 1 | 1/2 | 0/0 | 0/0 | **no** | yes | bg banner_event_chr_013 |
| `event_exp_green` | 緑の経験値素材ミッション | daily+weekly | 24 (2017-04-07..2021-03-19) | 3 | 0/0 | 1/1 | 4/4 | **no** | yes | bg banner_roleexHel_002 |
| `event_rim_11` | 連邦アカデミーの新入生（１） | story | 2 (2017-04-13..2021-05-06) | 12 | 1/4 | 8/8 | 14/14 | **no** | **no** | bg banner_event_chr_023; banner banner_event_chr_022 |
| `event_exp_blue` | 青の経験値素材ミッション | daily+weekly | 52 (2017-04-27..2021-03-26) | 3 | 0/0 | 1/1 | 3/3 | **no** | yes | bg banner_roleexShu_002 |
| `event_axb_15` | ＳＯ４雑魚イベント | story | 13 (2017-05-11..2021-03-25) | 9 | 1/4 | 2/2 | 5/5 | yes | yes |  |
| `event_alm_16` | ＳＯ４ボスイベント | story | 12 (2017-05-25..2021-04-22) | 9 | 1/4 | 3/3 | 7/7 | yes | yes |  |
| `event_exp_yellow` | 黄の経験値素材ミッション | daily+weekly | 32 (2017-05-25..2021-04-08) | 3 | 0/0 | 1/1 | 3/3 | **no** | yes | bg banner_roleexDef_002 |
| `event_arm_21` | SO5アドヒジョン・アルマ戦＋後日談 | story | 12 (2017-06-29..2021-04-29) | 13 | 0/8 | 1/1 | 4/4 | yes | yes |  |
| `event_sum_22` | 水着イベント前半 | story | 4 (2017-07-13..2021-05-20) | 17 | 0/10 | 3/3 | 7/7 | **no** | **no** | bg bbg91_09_01; banner banner_event_chr_032 |
| `event_sum_23` | 水着イベント後半 | story | 4 (2017-07-27..2021-05-06) | 16 | 0/9 | 4/4 | 5/5 | **no** | **no** | bg bbg91_10_02; banner banner_event_chr_033 |
| `event_mir_24` | 副官イベント | story | 13 (2017-08-10..2021-05-06) | 11 | 0/6 | 1/1 | 7/7 | **no** | **no** | bg banner_event_chr_034; banner banner_event_chr_035 |
| `event_cra_25` | 弓クロードイベント | story | 2 (2017-08-24..2021-05-06) | 6 | 0/4 | 1/1 | 5/5 | **no** | **no** | bg banner_event_chr_036; banner banner_event_chr_036 |
| `event_asm_26` | 双龍祓い落しイベント | story | 13 (2017-08-31..2021-05-06) | 14 | 0/9 | 2/2 | 8/8 | **no** | **no** | bg banner_event_chr_037; banner banner_event_chr_037 |
| `event_prb_28` | プリシス＆ベルダイベント | story | 12 (2017-09-14..2020-03-12) | 14 | 0/9 | 2/2 | 5/5 | **no** | **no** | bg banner_event_so2_003; banner banner_event_so2_003 |
| `event_ffbe_27` | -- | story | 2 (2017-09-28..2019-08-29) | 22 | 0/11 | 4/4 | 13/13 | **no** | **no** | bg bbc02_01_01; banner banner_event_chr_038 |
| `event_aca_28` | アカデミー時代イベント | story | 12 (2017-10-12..2020-03-19) | 13 | 0/8 | 3/3 | 6/6 | **no** | **no** | bg banner_event_chr_039; banner banner_event_chr_039 |
| `event_ticket_02` | チケットミッション | daily | 1 (2017-10-26..2019-09-26) | 14 | 0/0 | 14/14 | 22/22 | **no** | yes | bg banner_ticket_event_001 |
| `event_leon_32` | レオンイベント | story | 12 (2017-11-30..2020-03-26) | 13 | 0/8 | 2/2 | 8/8 | yes | **no** | banner banner_event_chr_042 |
| `event_ren_33_02` | ＶＰイベント　Ｂパート | story | 3 (2018-01-11..2021-03-04) | 15 | 0/9 | 1/1 | 3/3 | **no** | **no** | bg bbg91_01_02; banner banner_event_chr_046 |
| `event_valentine_34` | 贈り物に込めた想い | story | 5 (2018-01-31..2021-05-20) | 13 | 0/7 | 3/3 | 8/8 | – | **no** | banner banner_event_chr_048 |
| `event_sius_35` | シウスイベント | story | 11 (2018-02-15..2020-04-02) | 13 | 0/8 | 2/2 | 10/10 | – | **no** | banner banner_event_chr_049 |
| `event_maid_39` | メイドネルクレアイベント | story | 5 (2018-03-29..2021-05-20) | 12 | 0/6 | 2/2 | 8/8 | – | **no** | banner banner_event_chr_052 |
| `event_afl_40` | エイプリルフール2018 | story | 1 (2018-04-01..2018-04-01) | 3 | 0/3 | 1/1 | 2/2 | – | – |  |
| `event_ope_41` | オペラアルベルイベント | story | 10 (2018-04-12..2020-04-09) | 13 | 0/7 | 2/2 | 9/9 | – | **no** | banner banner_event_chr_054 |
| `event_mel_43` | メリクルルシフェルイベント | story | 9 (2018-05-17..2020-04-16) | 12 | 0/6 | 1/1 | 7/7 | – | **no** | banner banner_event_chr_056 |
| `event_rad_44` | -- | story | 3 (2018-05-20..2019-05-30) | 5 | 0/3 | 2/2 | 1/1 | yes | **no** | banner banner_event_chr_057 |
| `event_ill_47` | イラストコンテスト | story | 4 (2018-06-28..2021-05-20) | 14 | 0/7 | 3/3 | 6/6 | yes | **no** | banner banner_event_chr_060 |
| `event_asp_48` | 灼炎のアシュトンイベント | story | 8 (2018-07-12..2020-04-23) | 14 | 0/7 | 2/2 | 8/8 | yes | **no** | banner banner_event_chr_061 |
| `event_yuin_52` | ユーインBSオペライベント | story | 6 (2018-09-13..2020-05-14) | 14 | 0/7 | 3/3 | 8/8 | – | **no** | banner banner_event_chr_065 |
| `event_casino_53` | カジノイベント | worldboss+bighunt+story | 1 (2018-09-27..2018-10-18) | 21 | 0/6 | 1/1 | 8/8 | yes | **no** | banner banner_event_chr_066 |
| `event_wel_54` | BASウェルチイベント | story | 6 (2018-10-11..2020-05-21) | 13 | 0/6 | 2/2 | 8/8 | – | **no** | banner banner_event_chr_067 |
| `event_max_38` | 覇級イベント | battle | 165 (2018-10-25..2021-06-22) | 1 | 0/0 | 1/1 | 1/1 | – | **no** | banner banner_event_so1_100 |
| `event_aru_56` | エイルマットカーリンイベント | story | 6 (2018-11-15..2020-05-28) | 14 | 0/7 | 2/2 | 8/8 | – | **no** | banner 20181122_event_001 |
| `event_BossRush_33` | 逆襲の三巨頭 | battle | 1 (2018-12-27..2018-12-31) | 2 | 0/0 | 1/1 | 4/4 | – | **no** | banner banner_event_chr_043 |
| `event_nier_36` | -- | story | 1 (2018-12-27..2019-01-10) | 73 | 0/9 | 1/1 | 8/8 | **no** | **no** | bg bbg91_17_02; banner banner_event_chr_050 |
| `event_valentine_61` | バレンタイン2019イベント | story | 4 (2019-02-01..2021-06-03) | 15 | 0/8 | 2/2 | 7/7 | – | **no** | banner 20190131_event_001 |
| `event_valcahenri_62` | ヴァルカアンリイベント | story | 5 (2019-02-14..2020-06-04) | 15 | 0/8 | 2/2 | 7/7 | – | **no** | banner 20190214_event_001 |
| `event_afl2019_65` | エイプリルフール2019 | story | 1 (2019-04-01..2019-04-01) | 4 | 0/4 | 1/1 | 1/1 | – | **no** | banner 20190328_event_002 |
| `event_tic_67` | 大人ティカ・リカルドイベント | story | 4 (2019-04-11..2020-06-11) | 14 | 0/7 | 1/1 | 7/7 | yes | **no** | banner 20190411_event_001 |
| `event_Guilty_70` | -- | story | 2 (2019-04-25..2021-02-18) | 20 | 0/10 | 3/3 | 7/7 | **no** | **no** | bg hcg1001_b01a; banner 20190425_event_001 |
| `event_OverRoad` | 覇王の挑戦 | battle | 1 (2019-05-01..2019-05-09) | 2 | 0/0 | 1/1 | 3/3 | – | **no** | banner 20181129_event_002 |
| `event_Souffle_68` | スフレノエルイベント | story | 4 (2019-05-09..2020-07-09) | 14 | 0/7 | 1/1 | 9/9 | – | **no** | banner 20190509_event_001 |
| `event_radio2_69` | -- | story | 1 (2019-05-23..2019-05-30) | 7 | 0/5 | 1/1 | 3/3 | yes | **no** | banner 20190523_event_001 |
| `event_sum_49` | 【180726】水着前半イベント | story | 3 (2019-07-18..2021-05-20) | 14 | 0/7 | 3/3 | 8/8 | **no** | **no** | bg bbg91_08_01; banner banner_event_chr_062 |
| `event_sww2019_75` | 水着イベント2019前半 | story | 3 (2019-07-18..2021-06-03) | 15 | 0/8 | 1/1 | 5/5 | yes | **no** | banner 20190718_event_001 |
| `event_sum_50` | 【180809】水着後半イベント | story | 3 (2019-07-31..2021-05-20) | 15 | 0/8 | 2/2 | 7/7 | **no** | **no** | bg bbg91_08_01; banner banner_event_chr_063 |
| `event_sww2019_76` | 水着イベント2019後半 | story | 3 (2019-07-31..2021-06-03) | 17 | 0/10 | 1/1 | 8/8 | yes | **no** | banner 20190731_event_001 |
| `event_iracon_78` | 2019イラコンイベント | story | 3 (2019-08-29..2021-06-03) | 15 | 0/7 | 3/3 | 9/9 | yes | **no** | banner 20190829_event_001 |
| `event_bstr_79` | BSチサトレオンイベント | story | 2 (2019-09-12..2020-09-03) | 15 | 0/7 | 2/2 | 5/5 | yes | **no** | banner 20190912_event_001 |
| `event_maid_80` | 2019メイドイベント第三段 | story | 4 (2019-09-26..2021-06-03) | 15 | 0/7 | 2/2 | 10/10 | yes | **no** | banner 20190926_event_001 |
| `event_ticket_03` | チケットミッション | daily | 1 (2019-09-26..2030-05-31) | 30 | 0/0 | 14/14 | 22/22 | **no** | yes | bg banner_ticket_event_001 |
| `event_PSNC1_81` | -- | story | 1 (2019-10-10..2019-11-07) | 16 | 0/7 | 2/2 | 6/6 | **no** | **no** | bg 00_bm0035_b01a_01; banner 20191017_event_001 |
| `event_Bow_74` | 恒常ボーマンイベント | story | 2 (2019-12-19..2020-07-16) | 13 | 0/6 | 1/1 | 9/9 | – | **no** | banner 20190711_event_001 |
| `event_erisu_77` | エリスヨシュアイベント | story | 2 (2019-12-19..2020-08-30) | 18 | 0/10 | 2/2 | 6/6 | yes | **no** | banner 20190815_event_001 |
| `event_BossRush_2019` | チケットミッション | battle | 1 (2019-12-26..2019-12-31) | 2 | 0/0 | 1/1 | 6/6 | **no** | **no** | bg banner_ticket_event_001; banner 20191226_event_001 |
| `event_newyear_59` | 正月&SRFイベント | story | 3 (2020-01-06..2021-06-03) | 16 | 0/10 | 1/1 | 5/5 | yes | **no** | banner 20190101_event_001 |
| `event_Valentine_2020` | チョコレート・イン・ザ・ヘル | battle | 1 (2020-02-13..2020-03-05) | 3 | 0/0 | 1/1 | 3/3 | yes | **no** | banner 20200220_event_001 |
| `event_April2020` | エイプリルフール2020 | story | 1 (2020-04-01..2020-04-01) | 3 | 0/3 | 1/1 | 1/1 | – | **no** | banner 20200326_event_002 |
| `event_idol2_64` | アイドルイベント第二弾 | story | 4 (2020-04-16..2021-06-03) | 16 | 0/9 | 7/7 | 10/10 | yes | yes |  |
| `event_idol_58` | アイドルイベント | story | 4 (2020-04-16..2021-05-20) | 16 | 0/9 | 5/5 | 7/7 | yes | **no** | banner 20181129_event_001 |
| `event_radiata_66` | ラジアータコラボ | story | 1 (2020-05-21..2020-06-11) | 17 | 0/10 | 2/2 | 7/7 | yes | **no** | banner 20190328_event_001 |
| `event_wed_45` | 花嫁前半 | story | 2 (2020-06-11..2021-05-20) | 42 | 0/16 | 2/2 | 10/10 | yes | **no** | banner banner_event_chr_059 |
| `event_VP2_92` | アリーシャルーファスイベント | story | 2 (2020-07-09..2021-03-04) | 15 | 0/7 | 3/3 | 5/5 | **no** | **no** | bg bbg90_07_02; banner 20200709_event_001 |
| `event_Memory_Last` | 忘却の聖地ワドラム最終刻 | story | 1 (2021-04-22..2021-05-13) | 17 | 0/12 | 2/2 | 3/3 | yes | **no** | banner 20210422_event_001 |

### BROKEN (35)

| event | name | kind | terms (first..last) | missions | scripts | maps | enemies | bg | banner | missing |
|---|---|---|---|---|---|---|---|---|---|---|
| `event_ren_03` | ＶＰイベント（黒レナス） | story | 3 (2017-01-26..2021-03-04) | 8 | 1/3 | 0/1 | 1/1 | **no** | **no** | maps bg90_21; bg banner_event_vp_002; banner banner_event_vp_002 |
| `event_apr_12_02` | 続・エイプリルフール | story | 1 (2017-04-06..2017-04-27) | 7 | 1/3 | 0/1 | 1/1 | **no** | – | maps bg91_03; bg banner_event_chr_014 |
| `event_apr_12_03_01` | ある日の生徒会室 | story | 1 (2017-04-13..2017-04-15) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_015 |
| `event_apr_12_03_02` | ある日の教室 | story | 1 (2017-04-15..2017-04-17) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_016 |
| `event_apr_12_03_03` | ある日の講堂 | story | 1 (2017-04-17..2017-04-19) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_017 |
| `event_apr_12_03_04` | ある日の保健室 | story | 1 (2017-04-19..2017-04-21) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_018 |
| `event_apr_12_03_05` | ある日の体育館 | story | 1 (2017-04-21..2017-04-23) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_019 |
| `event_apr_12_03_06` | ある日の部室 | story | 1 (2017-04-23..2017-04-25) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_020 |
| `event_apr_12_03_07` | ある日のグラウンド | story | 1 (2017-04-25..2017-04-27) | 2 | 1/2 | 0/1 | 3/3 | **no** | – | maps bg91_03; bg banner_event_chr_021 |
| `event_hall_29` | ハロウィンイベント | story | 3 (2017-10-26..2021-05-06) | 13 | 0/8 | 0/1 | 8/8 | **no** | **no** | maps bg91_14; bg bbg91_14_02; banner banner_event_chr_069 |
| `event_ud1_30` | ＵＤイベント | story | 2 (2017-11-16..2019-07-25) | 14 | 0/9 | 1/1 | 0/2 | **no** | **no** | enemies cm414_b01a cm415_b01a; bg banner_event_chr_041; banner banner_event_chr_041 |
| `event_ren_33` | ＶＰイベント　Ａパート | story | 3 (2017-12-28..2021-03-04) | 16 | 0/9 | 1/2 | 4/4 | **no** | **no** | maps bc01_03; bg bbc01_03_01; banner banner_event_chr_045 |
| `event_ren_33_03` | ＶＰイベント　Ｃパート | story | 3 (2018-01-18..2021-03-04) | 22 | 0/14 | 0/2 | 3/3 | **no** | **no** | maps bc01_02 bc01_03; bg bbc01_02_02; banner banner_event_chr_047 |
| `event_mar_37` | マリアディアスイベント | story | 3 (2018-03-15..2021-05-20) | 13 | 0/7 | 0/1 | 9/9 | **no** | **no** | maps bg91_18; bg bbg91_18_02; banner banner_event_chr_051 |
| `event_eoe_14` | -- | story | 3 (2018-04-26..2020-05-07) | 8 | 1/3 | 0/1 | 0/1 | **no** | **no** | maps bc01_01; enemies cm412_b01a; bg banner_event_chr_024; banner banner_event_chr_024 |
| `event_wed_17` | ウェディング前半 | story | 3 (2018-05-31..2021-05-06) | 16 | 0/10 | 1/2 | 6/6 | **no** | **no** | maps bg91_04; bg banner_event_chr_027; banner banner_event_chr_026 |
| `event_wed_19` | ウェディング後半 | story | 3 (2018-06-14..2021-05-06) | 15 | 0/8 | 1/3 | 4/4 | **no** | **no** | maps bg91_04 bg91_05; bg banner_event_chr_030; banner banner_event_chr_029 |
| `event_maid_51` | メイドソフィア・執事レオン | story | 5 (2018-08-30..2021-05-20) | 13 | 0/7 | 2/3 | 8/8 | – | **no** | maps bg91_05; banner banner_event_chr_064 |
| `event_eoe_42` | -- | story | 2 (2018-10-11..2020-05-07) | 16 | 0/9 | 0/2 | 5/6 | – | **no** | maps bc01_01 bc01_04; enemies cm421_b01a; banner banner_event_chr_055 |
| `event_hal_55` | ハロウィン2018イベント | story | 3 (2018-10-25..2021-05-20) | 17 | 0/8 | 1/2 | 10/10 | **no** | **no** | maps bm0012_b01a; bg ebg0012_b01a_01; banner banner_event_chr_068 |
| `event_Xmas_57` | クリスマス2018イベント | story | 4 (2018-12-13..2021-05-20) | 15 | 0/8 | 1/2 | 8/8 | – | **no** | maps bg91_15; banner 20181213_event_001 |
| `event_xmas_31` | クリスマスイベント | story | 4 (2018-12-27..2021-05-06) | 15 | 0/9 | 2/3 | 7/7 | **no** | yes | maps bg91_15; bg bbg91_15_02 |
| `event_sak_60` | -- | story | 2 (2019-01-17..2020-04-23) | 19 | 0/9 | 2/3 | 8/8 | **no** | **no** | maps bg91_18; bg bbg91_18_02; banner 20190117_event_001 |
| `event_shingeki_63` | -- | story | 1 (2019-02-28..2019-03-14) | 22 | 0/12 | 2/2 | 5/6 | **no** | **no** | enemies cm425_b01a; bg ebg0018_b01a_01; banner 20190228_event_001 |
| `event_TOP_1_71` | -- | story | 2 (2019-05-25..2020-11-05) | 15 | 0/7 | 1/2 | 5/5 | yes | **no** | maps bm0020_b01a; banner 20190525_event_001 |
| `event_TOP_2_72` | -- | story | 2 (2019-06-06..2020-11-05) | 17 | 0/9 | 1/4 | 6/6 | **no** | **no** | maps bm0020_b01a bm0021_b01a bm0021_b02a; bg ebg0021_b01a_01; banner 20190606_event_001 |
| `event_PSNC2_82` | -- | story | 1 (2019-10-24..2019-11-07) | 21 | 0/10 | 0/1 | 11/11 | **no** | **no** | maps bm0032_b01a; bg 00_bm0032_b01a_06; banner 20191031_event_001 |
| `event_3year_85` | 3周年イベント | story | 3 (2019-11-28..2021-06-03) | 20 | 0/11 | 3/4 | 9/9 | **no** | **no** | maps bg91_05; bg 00_bm0031_b01a_01; banner 20191128_event_001 |
| `event_god_86` | 神級イベント | god+ranking | 13 (2019-11-28..2021-06-24) | 85 | 0/0 | 2/3 | 31/32 | yes | yes | maps bm0034_b02a; enemies cm401_b01a |
| `event_Xmas3_84` | クリスマスイベント2019 | story | 3 (2019-12-12..2021-06-03) | 15 | 0/7 | 2/3 | 12/12 | **no** | **no** | maps bm0016_b01a; bg 00_bm0016_b01a_01; banner 20191212_event_001 |
| `event_Guilty_88` | -- | story | 2 (2020-01-30..2021-02-18) | 17 | 0/8 | 4/4 | 10/11 | **no** | **no** | enemies cc0028_b02a; bg hcg1001_b01a; banner 20200130_event_001 |
| `event_sak_90` | -- | story | 1 (2020-03-26..2020-04-23) | 21 | 0/10 | 2/3 | 9/9 | **no** | **no** | maps bg91_18; bg bbg91_18_02; banner 20200409_event_001 |
| `event_Bride2019_73` | 花嫁2019イベント | story | 2 (2020-06-04..2021-06-03) | 14 | 0/7 | 2/3 | 6/6 | **no** | **no** | maps bm0023_b01a; bg 00_bm0023_b01a_01; banner 20190627_event_001 |
| `event_FT2019_83` | ハロウィン2019（童話イベント） | story | 2 (2020-11-05..2021-06-03) | 17 | 0/9 | 0/1 | 8/8 | **no** | **no** | maps bm0026_b01a; bg 00_bm0026_b01a_01; banner 20191107_event_001 |
| `event_VP_94` | VPヴァルキリーレザードイベント | story | 1 (2021-02-18..2021-03-04) | 18 | 0/9 | 3/3 | 4/5 | **no** | **no** | enemies cm408_b02a; bg bbg91_16_01; banner 20200924_event_002 |

### NO-MISSIONS (12)

| event | name | kind | terms (first..last) | missions | scripts | maps | enemies | bg | banner | missing |
|---|---|---|---|---|---|---|---|---|---|---|
| `event_wel_04_01` | 聖夜の贈り物大作戦（１） | battle | 1 (2016-12-08..2017-01-05) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_001; banner banner_event_chr_001 |
| `event_wel_04_02` | 聖夜の贈り物大作戦（２） | battle | 1 (2016-12-15..2017-01-05) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_002; banner banner_event_chr_001 |
| `event_mem_01` | 慰霊祭（１） | battle | 1 (2017-01-05..2017-02-02) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_004; banner banner_event_chr_004 |
| `event_mem_02` | 慰霊祭（２） | battle | 1 (2017-01-12..2017-02-02) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_005; banner banner_event_chr_004 |
| `event_ren_03_02` | ＶＰイベント（黒レナス） | battle | 84 (2017-02-02..2017-02-23) | 0 | 0/0 | 0/0 | 0/0 | **no** | – | bg banner_event_vp_003 |
| `event_val_01` | チョコレート・パニック（１） | battle | 1 (2017-02-02..2017-03-02) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_007; banner banner_event_chr_007 |
| `event_val_02` | チョコレート・パニック（２） | battle | 1 (2017-02-09..2017-03-02) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_chr_008; banner banner_event_chr_007 |
| `event_mic_06_02` | ＳＯ２ミカエル降臨イベント滅級 | battle | 84 (2017-03-02..2017-03-23) | 0 | 0/0 | 0/0 | 0/0 | **no** | – | bg banner_event_so2_004 |
| `event_luc_13_02` | SO3ルシファー降臨　滅級 | battle | 1 (2017-03-30..2017-04-13) | 0 | 0/0 | 0/0 | 0/0 | **no** | **no** | bg banner_event_so3_002; banner banner_gacha_pickup_role_0054 |
| `event_eoe_14_02` | -- | battle | 1 (2017-05-04..2017-05-31) | 0 | 0/0 | 0/0 | 0/0 | **no** | – | bg banner_event_chr_025 |
| `event_axb_15_02` | ＳＯ４雑魚イベント　滅級 | battle | 1 (2017-05-18..2017-05-31) | 0 | 0/0 | 0/0 | 0/0 | yes | **no** | banner banner_gacha_pickup_role_0056 |
| `event_wed_20` | ウェディング妄想シナリオ | battle | 1 (2017-05-31..2017-07-06) | 0 | 0/0 | 0/0 | 0/0 | **no** | – | bg banner_event_chr_031 |

Missing across all events: 20 battle maps (bc01_01 bc01_02 bc01_03 bc01_04 bg90_21 bg91_03 bg91_04 bg91_05 bg91_14 bg91_15 bg91_18 bm0012_b01a bm0016_b01a bm0020_b01a bm0021_b01a bm0021_b02a bm0023_b01a bm0026_b01a bm0032_b01a bm0034_b02a); 8 enemy models (cc0028_b02a cm401_b01a cm408_b02a cm412_b01a cm414_b01a cm415_b01a cm421_b01a cm425_b01a); talk scripts 645 of 767 (per-event counts above).

## Event guide

What each event was, ordered by first term. **About** is a hand-written English summary from `docs/event-notes.tsv` (interpretation of the data; "likely" marks guesses). The other lines come straight from master data (the game's Japanese text): story chapters, battle missions, difficulty tiers, the bosses of the highest-level mission, event drop currencies, gachas that opened within two days of the event, world boss.

#### `event_ticket` — チケットミッション · PLAYABLE

- **About:** Ticket missions (2016–17): ticket-entry versions of the ingot and EXP-material dailies.
- **Kind:** daily; 36 missions; terms 2016-01-01 .. 2017-10-26 (1); recommended level up to 50
- **Battles:** インゴットミッション / 経験値素材アタッカー / 経験値素材キャスター / 経験値素材シューター / 経験値素材ディフェンダー / 経験値素材ヒーラー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** ゲレル・サン / ホーンドタートル / 金の妖精
- **Gachas opening alongside:** ★5エース確定キャラガチャ(10連、期間中1人1回) / ★３武器ガチャチケット / ★４キャラガチャチケット / ★４武器ガチャチケット

#### `event_so1_01` — ＳＯ１イベント（ゲレル） · PLAYABLE

- **About:** STAR OCEAN 1 crossover event: a Gerel (slime) outbreak; two story chapters plus Gerel-swarm hunts; Gerel legacy coins. Rerun later.
- **Kind:** story; 7 missions; terms 2016-12-01 .. 2020-11-26 (12); recommended level up to 96
- **Story (2):** 異常事態発生 / 異常事態の収束
- **Battles:** ゲレル大群生の討伐
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** ゲレル・マミー / ゲレル・ダディ / ストローパー / ゲレル・サン
- **Event currency / drops:** ゲレル・レガシーコイン / 復刻コイン

#### `event_wel_04_01` — 聖夜の贈り物大作戦（１） · NO-MISSIONS

- **About:** "Operation Christmas Present" part 1 (Dec 2016) — container with no missions of its own.
- **Kind:** battle; 0 missions; terms 2016-12-08 .. 2017-01-05 (1)

#### `event_wel_04_02` — 聖夜の贈り物大作戦（２） · NO-MISSIONS

- **About:** "Operation Christmas Present" part 2 — container with no missions of its own.
- **Kind:** battle; 0 missions; terms 2016-12-15 .. 2017-01-05 (1)
- **Gachas opening alongside:** ２００万ＤＬ記念キャラガチャ（１人１回）

#### `event_so1_02` — ＳＯ１イベント（ジエ・リヴォース） · PLAYABLE

- **About:** STAR OCEAN 1 crossover: the tyrant Jie Revorse appears; escape from another dimension; Jie Revorse boss and coins.
- **Kind:** story; 7 missions; terms 2016-12-22 .. 2021-01-07 (13); recommended level up to 132
- **Story (2):** 稀代の独裁者出現 / 異空間からの脱出
- **Battles:** ジエ・リヴォース降臨
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** ジエ・リヴォース
- **Event currency / drops:** ジエ・リヴォースコイン / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ

#### `event_wel_04_03` — 聖夜の贈り物大作戦（３） · PLAYABLE

- **About:** "Operation Christmas Present" (1)–(3): short Christmas 2016 story event.
- **Kind:** story; 3 missions; terms 2016-12-22 .. 2021-05-06 (2); recommended level up to 20
- **Story (3):** 聖夜の贈り物大作戦（１） / 聖夜の贈り物大作戦（２） / 聖夜の贈り物大作戦（３）
- **Achievement tag:** イベント
- **Gachas opening alongside:** ピックアップガチャ

#### `event_new_01` — 大そうじの心得 · PLAYABLE

- **About:** Year-end "big cleaning" one-mission story event (Dec 2016).
- **Kind:** story; 1 missions; terms 2016-12-28 .. 2017-01-12 (1); recommended level up to 20
- **Story (1):** 大そうじの心得
- **Gachas opening alongside:** ３００万ＤＬ記念キャラガチャ（１人１回）

#### `event_new_02` — ハッピーニューイヤー · PLAYABLE

- **About:** "Happy New Year" 2017 one-mission story event.
- **Kind:** story; 1 missions; terms 2017-01-01 .. 2017-01-12 (1); recommended level up to 20
- **Story (1):** ハッピーニューイヤー
- **Achievement tag:** イベント

#### `event_wep_exp` — ハンマーミッション · FULL

- **About:** Daily "hammer" missions: weapon-EXP material (Hammer Golem).
- **Kind:** daily; 1 missions; terms 2017-01-04 .. 2020-05-21 (16); recommended level up to 60
- **Battles:** ハンマーミッション
- **Bosses (hardest mission):** サーベルタイガー / ハンマーゴーレム
- **Gachas opening alongside:** ピックアップガチャ

#### `event_mem_01` — 慰霊祭（１） · NO-MISSIONS

- **About:** Memorial service (慰霊祭) part 1 (Jan 2017) — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-01-05 .. 2017-02-02 (1)
- **Gachas opening alongside:** ピックアップガチャ

#### `event_mem_02` — 慰霊祭（２） · NO-MISSIONS

- **About:** Memorial service part 2 — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-01-12 .. 2017-02-02 (1)
- **Gachas opening alongside:** 日替ピックアップ武器ガチャ【剣&鞘】専用 / 日替ピックアップ武器ガチャ【杖】専用 / 日替ピックアップ武器ガチャ【片手剣】専用

#### `event_fro_04` — フロストツリー討伐 · PLAYABLE

- **About:** Frost Tree raid: high-difficulty (滅/獄) boss hunt dropping Frost coins.
- **Kind:** battle; 2 missions; terms 2017-01-19 .. 2019-04-25 (88); recommended level up to 154
- **Battles:** フロストツリー討伐
- **Difficulty tiers:** 滅級 獄級
- **Bosses (hardest mission):** サーベルタイガー / フロストツリー / 食人樹
- **Event currency / drops:** フロストコイン
- **Gachas opening alongside:** 日替ピックアップ武器ガチャ【ナックル】専用 / 日替ピックアップ武器ガチャ【剣&鞘】専用 / 日替ピックアップ武器ガチャ【杖】専用 / 日替ピックアップ武器ガチャ【片手剣】専用

#### `event_mem_03` — 慰霊祭（３） · PLAYABLE

- **About:** Memorial service (3): "The vow in the lantern" (1)–(3), short story event.
- **Kind:** story; 3 missions; terms 2017-01-19 .. 2021-05-06 (2); recommended level up to 20
- **Story (3):** ランタンに込めた誓い（１） / ランタンに込めた誓い（２） / ランタンに込めた誓い（３）
- **Achievement tag:** イベント
- **Gachas opening alongside:** 日替ピックアップ武器ガチャ【ナックル】専用 / 日替ピックアップ武器ガチャ【剣&鞘】専用 / 日替ピックアップ武器ガチャ【杖】専用 / 日替ピックアップ武器ガチャ【片手剣】専用

#### `event_ren_03` — ＶＰイベント（黒レナス） · BROKEN

- **About:** Valkyrie Profile crossover: Blood Valkyrie (dark Lenneth) descends; two story chapters and a boss up to Annihilation rank.
- **Kind:** story; 8 missions; terms 2017-01-26 .. 2021-03-04 (3); recommended level up to 170
- **Story (2):** 水鏡が繋ぐ絆 / 神々も予期せぬ再会
- **Battles:** ブラッドヴァルキリー降臨
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** ブラッドヴァルキリー
- **Event currency / drops:** 血の戦乙女コイン / 復刻コイン / 血の戦乙女コイン【滅】
- **Gachas opening alongside:** ピックアップガチャ / 補填武器チケット / 補填武器チケット：ダガー / 補填武器チケット：ナックル

#### `event_ren_03_02` — ＶＰイベント（黒レナス） · NO-MISSIONS

- **About:** Valkyrie Profile Blood Valkyrie — extra container with no missions.
- **Kind:** battle; 0 missions; terms 2017-02-02 .. 2017-02-23 (84)

#### `event_val_01` — チョコレート・パニック（１） · NO-MISSIONS

- **About:** "Chocolate Panic" part 1 (Valentine 2017) — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-02-02 .. 2017-03-02 (1)

#### `event_val_02` — チョコレート・パニック（２） · NO-MISSIONS

- **About:** "Chocolate Panic" part 2 — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-02-09 .. 2017-03-02 (1)
- **Gachas opening alongside:** ピックアップガチャ

#### `event_bat_05` — ＳＯ２闘技場イベント · PLAYABLE

- **About:** STAR OCEAN 2 Arena event: a VR arena in the pleasure city (Fun City); simulator battles and simulator coins.
- **Kind:** story; 7 missions; terms 2017-02-16 .. 2021-01-14 (13); recommended level up to 105
- **Story (2):** 宇宙一の娯楽都市 / シミュレーター修理完了？
- **Battles:** ＶＲ闘技場バトル
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** レッサードラゴン / アヴァローニ / ゲレル・マミー / ゲレル・ダディ
- **Event currency / drops:** シミュレーターコイン / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ

#### `event_cry_07` — クリスタルガーディアン討伐 · PLAYABLE

- **About:** Crystal Guardian raid: high-difficulty boss hunt dropping Crystal coins.
- **Kind:** battle; 2 missions; terms 2017-02-16 .. 2018-06-28 (59); recommended level up to 154
- **Battles:** クリスタルガーディアン討伐
- **Difficulty tiers:** 滅級 獄級
- **Bosses (hardest mission):** カルディアノンゾルダ / クリスタルガーディアン / セイクリッドガード
- **Event currency / drops:** クリスタルコイン
- **Gachas opening alongside:** ピックアップガチャ

#### `event_val_03` — チョコレート・パニック（３） · PLAYABLE

- **About:** "Chocolate Panic" (1)–(3): Valentine 2017 story event.
- **Kind:** story; 3 missions; terms 2017-02-16 .. 2021-05-06 (2); recommended level up to 20
- **Story (3):** チョコレート・パニック（１） / チョコレート・パニック（２） / チョコレート・パニック（３）
- **Achievement tag:** イベント
- **Gachas opening alongside:** ピックアップガチャ

#### `event_mic_06` — ＳＯ２ミカエル降臨イベント · PLAYABLE

- **About:** STAR OCEAN 2 Michael (Ten Wise Men) descends: Fun City in flames; Michael boss and coins.
- **Kind:** story; 8 missions; terms 2017-02-23 .. 2021-01-28 (12); recommended level up to 170
- **Story (2):** ファンシティ大炎上 / 災いを転じて福となす
- **Battles:** 十賢者ミカエル降臨
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** ミカエル
- **Event currency / drops:** ミカエルコイン / 復刻コイン / ミカエルコイン【滅】
- **Gachas opening alongside:** ピックアップガチャ

#### `event_mic_06_02` — ＳＯ２ミカエル降臨イベント滅級 · NO-MISSIONS

- **About:** SO2 Michael Annihilation-rank add-on — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-03-02 .. 2017-03-23 (84)
- **Gachas opening alongside:** ピックアップ武器ガチャ

#### `event_spo_08` — ＳＯ３エクスキューショナー襲来 · PLAYABLE

- **About:** STAR OCEAN 3 Executioner invasion: defence operation against the Executioners/Proxies; coins.
- **Kind:** story; 7 missions; terms 2017-03-09 .. 2021-03-11 (13); recommended level up to 100
- **Story (2):** 神の裁きに抗う者たち / 防衛作戦成功
- **Battles:** エクスキューショナー襲来
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** 執行者 / 代弁者 / 金の妖精
- **Event currency / drops:** エクスキューショナーコイン / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(アルベル/イリア)

#### `event_exp_all` — 虹の経験値素材ミッション · FULL

- **About:** Daily EXP-material missions for all roles (rainbow).
- **Kind:** daily+weekly; 3 missions; terms 2017-03-16 .. 2021-06-24 (93); recommended level up to 50
- **Battles:** 経験値素材全ロール
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** レッサードラゴン / オキュペテ・ネクロマンシー / セイタンシルバー
- **Gachas opening alongside:** 人気キャラピックアップ / ４００万ＤＬ記念キャラガチャ（１人１回）

#### `event_mik_10` — 女ゴコロとひなあられ（３） · PLAYABLE

- **About:** Hinamatsuri (Girls' Day) 2017 short story event, (1)–(3).
- **Kind:** story; 3 missions; terms 2017-03-16 .. 2021-05-06 (2); recommended level up to 20
- **Story (3):** 女ゴコロとひなあられ（１） / 女ゴコロとひなあられ（２） / 女ゴコロとひなあられ（３）
- **Achievement tag:** イベント
- **Gachas opening alongside:** 人気キャラピックアップ / ４００万ＤＬ記念キャラガチャ（１人１回）

#### `event_exp_purple` — 紫の経験値素材ミッション · PLAYABLE

- **About:** Daily EXP-material missions, Caster role.
- **Kind:** daily+weekly; 3 missions; terms 2017-03-23 .. 2021-04-23 (38); recommended level up to 50
- **Battles:** 経験値素材キャスター
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** 宇宙海賊団・エリート団員 / ブラスドラゴン / セイタンシルバー
- **Gachas opening alongside:** ピックアップガチャ(フェイト/ソフィア)

#### `event_exp_red` — 赤の経験値素材ミッション · PLAYABLE

- **About:** Daily EXP-material missions, Attacker role.
- **Kind:** daily+weekly; 3 missions; terms 2017-03-23 .. 2021-04-23 (75); recommended level up to 50
- **Battles:** 経験値素材アタッカー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** キラーシザース / ゲレル・ダディ / セイタンシルバー
- **Gachas opening alongside:** ピックアップガチャ(フェイト/ソフィア)

#### `event_luc_13` — SO3ルシファー降臨 · PLAYABLE

- **About:** STAR OCEAN 3 Lucifer descends: the creator runs amok; Lucifer boss and coins.
- **Kind:** story; 8 missions; terms 2017-03-23 .. 2021-03-18 (13); recommended level up to 170
- **Story (2):** 創造主の暴走 / 全てが終わる時まで
- **Battles:** ルシファー降臨
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** ルシファー
- **Event currency / drops:** ルシファーコイン / 復刻コイン / ルシファーコイン【滅】
- **Gachas opening alongside:** ピックアップガチャ(フェイト/ソフィア)

#### `event_luc_13_02` — SO3ルシファー降臨　滅級 · NO-MISSIONS

- **About:** SO3 Lucifer Annihilation-rank add-on — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-03-30 .. 2017-04-13 (1)
- **Gachas opening alongside:** ピックアップ武器ガチャ

#### `event_apr_12` — エイプリルフール · PLAYABLE

- **About:** April Fools 2017: one-mission "fabricated reality" gag event.
- **Kind:** story; 1 missions; terms 2017-04-01 .. 2017-04-01 (1); recommended level up to 20
- **Story (1):** 捏造されたリアリティ
- **Gachas opening alongside:** ピックアップ武器ガチャ

#### `event_apr_12_02` — 続・エイプリルフール · BROKEN

- **About:** April Fools sequel (2017): "the strongest enemy?!" Koro Revorse parody boss; banana coins.
- **Kind:** story; 7 missions; terms 2017-04-06 .. 2017-04-27 (1); recommended level up to 130
- **Story (2):** あの日の続編！？ / あたしたちの歩み
- **Battles:** 最凶の敵！？襲来
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** コロ・リヴォース
- **Event currency / drops:** バナナコイン
- **Gachas opening alongside:** ピックアップガチャ(イヴリーシュ/ミカエル)

#### `event_exp_green` — 緑の経験値素材ミッション · PLAYABLE

- **About:** Daily EXP-material missions, Healer role.
- **Kind:** daily+weekly; 3 missions; terms 2017-04-07 .. 2021-03-19 (24); recommended level up to 50
- **Battles:** 経験値素材ヒーラー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** キラーシザース / バーベッドアーミー / シスターファンゴ / セイタンシルバー
- **Gachas opening alongside:** ピックアップガチャ(イヴリーシュ/ミカエル)

#### `event_apr_12_03_01` — ある日の生徒会室 · BROKEN

- **About:** "One day at school" series (Apr 2017, 2 days each): the student-council room — school-parody story + battle.
- **Kind:** story; 2 missions; terms 2017-04-13 .. 2017-04-15 (1); recommended level up to 40
- **Story (1):** ある日の生徒会室
- **Battles:** 不正勧誘を取り締まれ！
- **Gachas opening alongside:** ピックアップガチャ(ネル/クレア) / ピックアップガチャ(マリア/クリフ)

#### `event_rim_11` — 連邦アカデミーの新入生（１） · PLAYABLE

- **About:** "The Federation Academy freshman" (Rimle): story event with Rimle's challenges.
- **Kind:** story; 12 missions; terms 2017-04-13 .. 2021-05-06 (2); recommended level up to 100
- **Story (3):** 連邦アカデミーの新入生（１） / 連邦アカデミーの新入生（２） / 連邦アカデミーの新入生（３）
- **Battles:** リムルの挑戦 / 意地っ張りリムル / 特訓リムル
- **Difficulty tiers:** 上級 中級 初級 獄級 超級
- **Bosses (hardest mission):** スケルトンアーマー / セイタンシルバー / 金の妖精 / ケイブガーダー
- **Event currency / drops:** 新入生訓練コイン / 復刻コイン
- **Achievement tag:** イベント
- **Gachas opening alongside:** ピックアップガチャ(ネル/クレア) / ピックアップガチャ(マリア/クリフ)

#### `event_apr_12_03_02` — ある日の教室 · BROKEN

- **About:** "One day at school": the classroom ("Anamne Angels").
- **Kind:** story; 2 missions; terms 2017-04-15 .. 2017-04-17 (1); recommended level up to 40
- **Story (1):** ある日の教室
- **Battles:** 怪傑アナムネエンジェルズ！
- **Gachas opening alongside:** ピックアップガチャ(ネル/クレア) / ピックアップガチャ(マリア/クリフ) / ピックアップガチャ(ラティクス/ミリー)

#### `event_apr_12_03_03` — ある日の講堂 · BROKEN

- **About:** "One day at school": the auditorium.
- **Kind:** story; 2 missions; terms 2017-04-17 .. 2017-04-19 (1); recommended level up to 40
- **Story (1):** ある日の講堂
- **Battles:** 幼馴染の行方
- **Gachas opening alongside:** ピックアップガチャ(ネル/クレア) / ピックアップガチャ(ミュリア/アンヌ) / ピックアップガチャ(ラティクス/ミリー)

#### `event_apr_12_03_04` — ある日の保健室 · BROKEN

- **About:** "One day at school": the infirmary.
- **Kind:** story; 2 missions; terms 2017-04-19 .. 2017-04-21 (1); recommended level up to 40
- **Story (1):** ある日の保健室
- **Battles:** シュールレアリズムの逆襲！
- **Gachas opening alongside:** ピックアップガチャ(フェイト/ソフィア/アルベル) / ピックアップガチャ(ミュリア/アンヌ) / ピックアップガチャ(ラティクス/ミリー)

#### `event_apr_12_03_05` — ある日の体育館 · BROKEN

- **About:** "One day at school": the gym.
- **Kind:** story; 2 missions; terms 2017-04-21 .. 2017-04-23 (1); recommended level up to 40
- **Story (1):** ある日の体育館
- **Battles:** マネージャー道、邁進中！
- **Gachas opening alongside:** ピックアップガチャ(フィデル/ミキ/ヴィクトル) / ピックアップガチャ(フェイト/ソフィア/アルベル) / ピックアップガチャ(ミュリア/アンヌ)

#### `event_apr_12_03_06` — ある日の部室 · BROKEN

- **About:** "One day at school": the club room.
- **Kind:** story; 2 missions; terms 2017-04-23 .. 2017-04-25 (1); recommended level up to 40
- **Story (1):** ある日の部室
- **Battles:** からあげ弁当１００人前！
- **Gachas opening alongside:** ピックアップガチャ(クロード/レナ/ディアス) / ピックアップガチャ(フィデル/ミキ/ヴィクトル) / ピックアップガチャ(フェイト/ソフィア/アルベル)

#### `event_apr_12_03_07` — ある日のグラウンド · BROKEN

- **About:** "One day at school": the sports ground ("road to Koshien").
- **Kind:** story; 2 missions; terms 2017-04-25 .. 2017-04-27 (1); recommended level up to 40
- **Story (1):** ある日のグラウンド
- **Battles:** 甲子園への道程
- **Gachas opening alongside:** ピックアップガチャ(クロード/レナ/ディアス) / ピックアップガチャ(フィデル/ミキ/ヴィクトル) / ピックアップガチャ(リーンベル)

#### `event_exp_blue` — 青の経験値素材ミッション · PLAYABLE

- **About:** Daily EXP-material missions, Shooter role.
- **Kind:** daily+weekly; 3 missions; terms 2017-04-27 .. 2021-03-26 (52); recommended level up to 50
- **Battles:** 経験値素材シューター
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** カルディアノンゾルダ / カルディアノンゲネラ / セイタンシルバー
- **Gachas opening alongside:** ピックアップガチャ(クロード/レナ/ディアス) / ピックアップガチャ(リーンベル)

#### `event_eoe_14_02` — -- · NO-MISSIONS

- **About:** Add-on container (May 2017) with no missions; label suggests it belongs to the "eoe" crossover.
- **Kind:** battle; 0 missions; terms 2017-05-04 .. 2017-05-31 (1)
- **Gachas opening alongside:** GWスペシャルピックアップ（１日１回）

#### `event_axb_15` — ＳＯ４雑魚イベント · PLAYABLE

- **About:** STAR OCEAN 4 "small fry" event: hunting the legendary giant bird (Colossal Beak) and its egg; egg coins.
- **Kind:** story; 9 missions; terms 2017-05-11 .. 2021-03-25 (13); recommended level up to 170
- **Story (3):** 永遠の宝 / 発見、幻の巨鳥！？ / 美の道は険しい
- **Battles:** コロッサルビーク討伐 / 幻のタマゴを求めて
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** アルベロデアニマ / レディ・ホーク / ベイビーク / クレイターペリュトン
- **Event currency / drops:** エッグコイン / エッグコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(セリーヌ/サラ)

#### `event_axb_15_02` — ＳＯ４雑魚イベント　滅級 · NO-MISSIONS

- **About:** SO4 small-fry Annihilation-rank add-on — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-05-18 .. 2017-05-31 (1)
- **Gachas opening alongside:** ガールズピックアップ（１日１回）

#### `event_alm_16` — ＳＯ４ボスイベント · PLAYABLE

- **About:** STAR OCEAN 4 boss event: guided by an oracle, "Doraneko" detour, Armaros Depth descends; coins.
- **Kind:** story; 9 missions; terms 2017-05-25 .. 2021-04-22 (12); recommended level up to 170
- **Story (3):** 神託に導かれて / どらねこの寄り道 / 異形の結晶
- **Battles:** どらねこの捜索 / アルマロス・デプス降臨
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** アルマロス・デプス / メタルシェルホーネット
- **Event currency / drops:** アルマロスコイン / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ガールズピックアップ（１日１回） / ピックアップガチャ(エッジ/メリクル) / ピックアップ武器ガチャ / ピックアップ武器ガチャ（１人１回）

#### `event_exp_yellow` — 黄の経験値素材ミッション · PLAYABLE

- **About:** Daily EXP-material missions, Defender role.
- **Kind:** daily+weekly; 3 missions; terms 2017-05-25 .. 2021-04-08 (32); recommended level up to 50
- **Battles:** 経験値素材ディフェンダー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** ヴァリアントアーミー / ゲレル・サン / セイタンシルバー
- **Gachas opening alongside:** ガールズピックアップ（１日１回） / ピックアップガチャ(エッジ/メリクル) / ピックアップ武器ガチャ / ピックアップ武器ガチャ（１人１回）

#### `event_evo_all` — 虹の進化素材ミッション · FULL

- **About:** Daily evolution-material missions for all roles (rainbow).
- **Kind:** daily+weekly; 3 missions; terms 2017-05-31 .. 2021-06-24 (89); recommended level up to 50
- **Battles:** 進化素材全ロール
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** キラーシザース / シスターファンゴ / アルベロデアニマ
- **Gachas opening alongside:** 6月の花嫁ピックアップガチャ(ネル/マリア) / CM放送記念キャラガチャ（１人１回）

#### `event_wed_20` — ウェディング妄想シナリオ · NO-MISSIONS

- **About:** "Wedding delusion scenario" (Jun 2017) — container with no missions.
- **Kind:** battle; 0 missions; terms 2017-05-31 .. 2017-07-06 (1)
- **Gachas opening alongside:** 6月の花嫁ピックアップガチャ(ネル/マリア) / CM放送記念キャラガチャ（１人１回）

#### `event_arm_21` — SO5アドヒジョン・アルマ戦＋後日談 · PLAYABLE

- **About:** STAR OCEAN 5 Adhesion Alma battle plus epilogue; several ship's-log (航海日誌) side stories.
- **Kind:** story; 13 missions; terms 2017-06-29 .. 2021-04-29 (12); recommended level up to 200
- **Story (6):** 【航海日誌】時空を超えた再会 / 【航海日誌】探究心の果てに…… / 【航海日誌】お絵かきしようよ！ / 少女の慟哭 / …
- **Battles:** アドヒジョン・アルマ戦 / 時空紋章で創られし空間
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** アドヒジョン・アルマ
- **Event currency / drops:** クロノスパレスコイン / クロノスパレスコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** キャスターピックアップ確定ガチャ（毎日１回） / ピックアップガチャ(フィオーレ/リリア)

#### `event_sum_22` — 水着イベント前半 · PLAYABLE

- **About:** Swimsuit event, first half (2017): ocean planet resort; rescue "Onigumo"; resort dates with Miki / Muria.
- **Kind:** story; 17 missions; terms 2017-07-13 .. 2021-05-20 (4); recommended level up to 200
- **Story (8):** 青き海の惑星 / オニグモの正体 / 異形の刺客 / ロビンの願い / …
- **Battles:** オニグモを救出せよ！ / ミキとのオーシャンリゾート / ミュリアとのオーシャンリゾート / 海底王を守れ！ / 海底王国探検
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** キラーシザース / ウェービングシザー / ゲレル・サン / フロストツリー
- **Event currency / drops:** コーダル【朱】 / マーレゼリアコイン【青】 / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(常夏のミキ/常夏のミュリア)

#### `event_acc_exp` — スレッドミッション · FULL

- **About:** Daily "thread" missions: accessory-EXP material.
- **Kind:** daily; 1 missions; terms 2017-07-27 .. 2020-05-21 (15); recommended level up to 60
- **Battles:** スレッドミッション
- **Bosses (hardest mission):** ハニービー / ホーンドタートル / スレッドビースト
- **Gachas opening alongside:** CM放送記念★5エース1体確定キャラガチャ(10連のみ、期間中1人1回) / ピックアップガチャ(常夏のレイミ/常夏のソフィア) / ピックアップ武器ガチャ（毎日１回）

#### `event_sum_23` — 水着イベント後半 · PLAYABLE

- **About:** Swimsuit event, second half (2017): resort dates with Sophia / Reimi; the broken sea king.
- **Kind:** story; 16 missions; terms 2017-07-27 .. 2021-05-06 (4); recommended level up to 200
- **Story (7):** 頼れる助っ人 / 開かれる扉 / 壊れた支配者と囚われの王妃 / 王国の最期 / …
- **Battles:** ソフィアとのオーシャンリゾート / レイミとのオーシャンリゾート / 海底王の仇討ち / 王宮への道 / 防護装置の捜索
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** イビルアイ系d
- **Event currency / drops:** コーダル【蒼】 / マーレゼリアコイン【緑】 / 復刻コイン
- **Gachas opening alongside:** CM放送記念★5エース1体確定キャラガチャ(10連のみ、期間中1人1回) / ピックアップガチャ(常夏のレイミ/常夏のソフィア) / ピックアップ武器ガチャ（毎日１回）

#### `event_mir_24` — 副官イベント · PLAYABLE

- **About:** Adjutant (副官) event: searching for Anne; Facula Dragon attack; ship's-log stories.
- **Kind:** story; 11 missions; terms 2017-08-10 .. 2021-05-06 (13); recommended level up to 200
- **Story (4):** 【航海日誌】信頼のかたち / 不協和音 / 晴れない暗雲 / 似た者同士
- **Battles:** アンヌを探して / ファキュラドラゴン急襲
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ブラスドラゴン / ハンマーゴーレム / ファキュラドラゴン / スティンガー
- **Event currency / drops:** クォークコイン / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップガチャ(ミラージュ/連邦アンヌ)

#### `event_cra_25` — 弓クロードイベント · PLAYABLE

- **About:** "Bow Claude" event: Claude with a bow; family stories (son / mother / father); Claude coins.
- **Kind:** story; 6 missions; terms 2017-08-24 .. 2021-05-06 (2); recommended level up to 100
- **Story (3):** 因果律のその先に（１） / 因果律のその先に（２） / 因果律のその先に（３）
- **Battles:** 息子の悩み / 母の慈愛 / 父の見解
- **Difficulty tiers:** 上級 獄級 超級
- **Bosses (hardest mission):** セイタンシルバー / 金の妖精 / スケルトンソルジャー / ウィザード
- **Event currency / drops:** クロードコイン / 復刻コイン
- **Gachas opening alongside:** 常夏キャラピックアップガチャ

#### `event_asm_26` — 双龍祓い落しイベント · PLAYABLE

- **About:** "Twin dragons" exorcism event: Salva mine monsters and a dungeon battle; ship's-log stories (Ashton).
- **Kind:** story; 14 missions; terms 2017-08-31 .. 2021-05-06 (13); recommended level up to 200
- **Story (7):** 【航海日誌】再会の一幕 / 【航海日誌】人気者はつらいよ / 【航海日誌】分かたれた兄妹 / 惑星エクスペル / …
- **Battles:** サルバ坑道の魔物 / 魔窟での死闘
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** チンケシーフ / トレント / ヴィドフニル / オキュペテ・ネクロマンシー
- **Event currency / drops:** ジオメテ・ジーネコイン / ジオメテ・ジーネコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(アシュトン/マーヴェル)

#### `event_prb_28` — プリシス＆ベルダイベント · PLAYABLE

- **About:** Precis & Welda event: an invention grand prix; Lucifer (Ten Wise Men) descends.
- **Kind:** story; 14 missions; terms 2017-09-14 .. 2020-03-12 (12); recommended level up to 200
- **Story (7):** 【航海日誌】果たし状！？ / 【航海日誌】グランプリ開催！ / 【航海日誌】優勝は誰だ？ / 人工惑星エナジーネーデ / …
- **Battles:** 十賢者ルシフェル降臨 / 蔵書を取り返せ / 雪原のモンスター
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ルシフェル
- **Event currency / drops:** ギヴァウェイコイン / ギヴァウェイコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(プリシス/ベルダ)

#### `event_sed_exp` — シードミッション · FULL

- **About:** Daily "seed" missions: awakening seed material.
- **Kind:** daily; 1 missions; terms 2017-09-21 .. 2030-12-31 (1); recommended level up to 60
- **Battles:** シードミッション
- **Bosses (hardest mission):** シスターファンゴ / タイニーファンゴ / 食人樹
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** サポートメダルガチャ / ピックアップ属性武器ガチャ（期間中１日１回） / ピックアップ武器ガチャ / ピックアップ武器ガチャ（１人１回）

#### `event_ffbe_27` — -- · PLAYABLE

- **About:** FINAL FANTASY BRAVE EXVIUS collaboration (achievements are titled "FFBE collab"): two worlds overlap through dimensional rifts; long mission ladder up to 絶 rank.
- **Kind:** story; 22 missions; terms 2017-09-28 .. 2019-08-29 (2); recommended level up to 200
- **Story (10):** 重なり合う２つの世界 / 帰還への道程 / 宇宙飛行士の抱く夢（１） / 宇宙飛行士の抱く夢（２） / …
- **Battles:** 樹海に潜む次元の裂け目 / 次元の裂け目を求めて（１） / 次元の裂け目を求めて（２） / 次元の裂け目を求めて（３） / 洞穴で揺らぐ次元の裂け目 / 湧き出すモンスター
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ウェービングシザー / ナイトエグザイル / アクアレジア / ホーンドトータス
- **Event currency / drops:** スタークォーツ / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ★5エース確定キャラガチャ(10連、期間中1人1回) / ピックアップガチャ(レイン/フィーナ) / ピックアップ属性武器ガチャ（期間中１日１回） / ピックアップ武器ガチャ

#### `event_aca_28` — アカデミー時代イベント · PLAYABLE

- **About:** Academy-days event: training programme, "who protects Earth", unknown enemy.
- **Kind:** story; 13 missions; terms 2017-10-12 .. 2020-03-19 (12); recommended level up to 200
- **Story (6):** 【航海日誌】弟子入りの理由 / 【航海日誌】他人の空似？ / 訓練プログラム起動！ / 仮想空間での出会い / …
- **Battles:** アカデミー総合演習 / 地球を守護する者 / 正体不明の敵
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 宇宙海賊団・エリート団員 / マザーバイラスポッド
- **Event currency / drops:** アカデミーコイン / アカデミーコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** SO2キャラピックアップガチャ（期間中3回） / SO4HD発表記念エッジorレイミ確定ガチャ（１人１回） / ★5以上１体確定キャラガチャ（期間中１日１回） / ピックアップガチャ(クロウ/連邦エッジ/連邦レイミ)

#### `event_hall_29` — ハロウィンイベント · BROKEN

- **About:** Halloween 2017: glowing eyes on the bridge, ghost-costume operation, pumpkin monsters.
- **Kind:** story; 13 missions; terms 2017-10-26 .. 2021-05-06 (3); recommended level up to 200
- **Story (6):** 怪奇！ブリッジに光る目玉 / 逆転の奇策 / オバケなりきり大作戦！ / 今日はオバケの日 / …
- **Battles:** オバケ大豊作！ / 不気味な惑星探索
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ネクロマンサー / ファイアコープス / パンプキンツリー / 金の妖精
- **Event currency / drops:** パンプキンクッキー / ゴーストクッキー / 復刻コイン
- **Gachas opening alongside:** SO4キャラピックアップガチャ（期間中3回） / ★5以上１体確定キャラガチャ（期間中１日１回） / ピックアップ(悪魔クレア/吸血鬼ヴィクトル/狼ミリー）

#### `event_ticket_02` — チケットミッション · PLAYABLE

- **About:** Ticket missions (2017–19): ticket-entry ingot / thread / hammer missions.
- **Kind:** daily; 14 missions; terms 2017-10-26 .. 2019-09-26 (1); recommended level up to 60
- **Battles:** インゴットミッション / スレッドミッション / ハンマーミッション / 経験値素材アタッカー / 経験値素材キャスター / 経験値素材シューター
- **Difficulty tiers:** 上級
- **Bosses (hardest mission):** ハニービー / ホーンドタートル / スレッドビースト
- **Gachas opening alongside:** SO4キャラピックアップガチャ（期間中3回） / ★5以上１体確定キャラガチャ（期間中１日１回） / ピックアップ(悪魔クレア/吸血鬼ヴィクトル/狼ミリー）

#### `event_ud1_30` — ＵＤイベント · BROKEN

- **About:** "UD" crossover, likely INFINITE UNDISCOVERY (tri-Ace): beast-tamer Venbatt, prison escape; ship's-log stories.
- **Kind:** story; 14 missions; terms 2017-11-16 .. 2019-07-25 (2); recommended level up to 200
- **Story (7):** 【航海日誌】猛者たちのマーチ / 【航海日誌】お姫様ラプソディー / 【航海日誌】英雄に捧ぐバラード / 導きのペンダント / …
- **Battles:** 獣使いヴェンバット戦 / 監獄脱出作戦
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 獣使いヴェンバット / シール・ガンナー
- **Event currency / drops:** 月印コイン / 月印コイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(カペル/アーヤ）

#### `event_leon_32` — レオンイベント · PLAYABLE

- **About:** Leon event: stranded, an interview-reporting story; Mine cave; crest-creature stampede.
- **Kind:** story; 13 missions; terms 2017-11-30 .. 2020-03-26 (12); recommended level up to 200
- **Story (6):** 幸運な遭難 / 追跡取材、開始！ / 突撃インタビュー？ / 歴史の紡がれる瞬間 / …
- **Battles:** ミーネ洞窟探索 / 紋章生物大暴走！
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** シャイントーテム / ゲレル・マミー / キング・ゲレル
- **Event currency / drops:** 取材データ / スクープデータ / 復刻コイン
- **Gachas opening alongside:** ピックアップガチャ(レオン/青春のソフィア/チサト)

#### `event_ren_33` — ＶＰイベント　Ａパート · BROKEN

- **About:** Valkyrie Profile crossover, part A: Chapter 1 — Freya's prophecy, Lezard's hideout, Midgard.
- **Kind:** story; 16 missions; terms 2017-12-28 .. 2021-03-04 (3); recommended level up to 200
- **Story (7):** Ｃｈａｐｔｅｒ １ プロローグ / フレイアの予言 / 女神に睨まれた男 / 戦乙女降臨 / …
- **Battles:** レザードの隠れ家 / ロキの思念の扉 / 人間界ミッドガルド（１） / 人間界ミッドガルド（２） / 対決、レザード
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ブラッドヴァルキリー / レザード・ヴァレス
- **Event currency / drops:** 魔晶石 / 戦乙女のコイン【青】 / 復刻コイン
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** 10連で★5エース1体確定キャラガチャ(1人1回) / 【復刻】ピックアップキャラガチャ(レナス/シルメリア) / ピックアップキャラガチャ(蒼穹のレナス/フレイ) / 定常武器ガチャ【近接】【ナックル/双剣/剣&鞘/鎌】

#### `event_ren_33_02` — ＶＰイベント　Ｂパート · PLAYABLE

- **About:** Valkyrie Profile crossover, part B: Chapter 2 — a new god, rebellion, Villnore castle.
- **Kind:** story; 15 missions; terms 2018-01-11 .. 2021-03-04 (3); recommended level up to 170
- **Story (7):** Ｃｈａｐｔｅｒ ２ プロローグ / 新興の神 / 反乱の報せ / 聖騎士の誓い / …
- **Battles:** アリアの思念の扉 / ヴィルノア城内（１） / ヴィルノア城内（２） / ヴィルノア城内（３） / 対決、ガノッサ
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** バリスティックライノ / スペクトラルナイト
- **Event currency / drops:** 魔晶石 / 復刻コイン / 戦乙女のコイン【黒】
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** ステップ3で★5武器確定ガチャ１(10連★4以上確定) / ステップ3で★5武器確定ガチャ２(10連★4以上確定) / ステップ3で★5武器確定ガチャ３(10連★5新武器確定) / ピックアップキャラガチャ(アーリィ/アリューゼ)

#### `event_ren_33_03` — ＶＰイベント　Ｃパート · BROKEN

- **About:** Valkyrie Profile crossover, part C: Chapter 3 — the reincarnation curse, two sorcerers; Lezard Valeth boss.
- **Kind:** story; 22 missions; terms 2018-01-18 .. 2021-03-04 (3); recommended level up to 200
- **Story (12):** Ｃｈａｐｔｅｒ ３ プロローグ / 転生の呪 / ２人の魔術師 / そして螺旋の終わりへ / …
- **Battles:** レザードの思念の扉 / レザードの抗い / レザードの抗い（１） / レザードの抗い（２）[シングル専用] / レザードの捜索 / 亡失都市ディパン（１）
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** レザード・ヴァレス
- **Event currency / drops:** 魔晶石 / 戦乙女のコイン【紫】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(レザード/メルティーナ)

#### `event_valentine_34` — 贈り物に込めた想い · PLAYABLE

- **About:** Valentine 2018: "gifts filled with feelings" — failed/penitent Valentines; gathering chocolate ingredients.
- **Kind:** story; 13 missions; terms 2018-01-31 .. 2021-05-20 (5); recommended level up to 200
- **Story (6):** 踏み台バレンタイン / 失敗バレンタイン / 反省バレンタイン / 感謝のバレンタイン / …
- **Battles:** チョコの材料集め / 薬の素材集め
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 金の妖精 / セイタンシルバー / クリムゾン・ボイルドフィッシュ / オキュペテ・ネクロマンシー
- **Event currency / drops:** コインチョコ / コインチョコ【滅】 / 復刻コイン
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** バレンタインデーピックアップキャラガチャ / ピックアップキャラガチャ(イヴリーシュ)

#### `event_sius_35` — シウスイベント · PLAYABLE

- **About:** Cyuss event: a warrior's continent (Astral), knight's trial.
- **Kind:** story; 13 missions; terms 2018-02-15 .. 2020-04-02 (11); recommended level up to 200
- **Story (6):** 【航海日誌】輝石に懸ける想い / 武人の地・アストラル大陸 / 騎士を志す者 / 汝が騎士道を示せ / …
- **Battles:** 神殿に現れし魔界の蟲 / 荒野の危険生物 / 騎士の試練への道
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ハニービー / マザーポリファーガオリジン / ゲレル・ダディ / ゲレル・サン
- **Event currency / drops:** アストラルコイン / アストラルコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** 600万DL記念武器ガチャ（期間中１日１回） / ピックアップキャラガチャ(赤麗のフィア/シウス)

#### `event_mar_37` — マリアディアスイベント · BROKEN

- **About:** Maria & Dias event: a hunting party that learns to cooperate; giant-bird / insect / beast hunts; cherry-blossom coins.
- **Kind:** story; 13 missions; terms 2018-03-15 .. 2021-05-20 (3); recommended level up to 200
- **Story (6):** 狩猟開始 / 乱れた連携 / まとまり始めた心 / 歩み出すために / …
- **Battles:** 巨大鳥討伐 / 昆虫討伐 / 獣討伐
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** エンシェントペリュトン / レオンブレード / スティンガー / ゲレル・ダディ
- **Event currency / drops:** 桜コイン / 桜コイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(桜花のマリア/桜雲のディアス)

#### `event_maid_39` — メイドネルクレアイベント · PLAYABLE

- **About:** Maid Nel & Clair event: missing footsteps, a war cameraman (Chisato), the governor's pet dragon.
- **Kind:** story; 12 missions; terms 2018-03-29 .. 2021-05-20 (5); recommended level up to 200
- **Story (5):** 消えた足どり / 戦場カメラマンの受難 / 【航海日誌】クリムゾン・メイド / ご主人様にお仕置きを / …
- **Battles:** チサトの捜索 / 前哨基地への道 / 総督の飼い竜
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** エメラルドドール / 海竜人 / ロッティングルーフ / ジョセフィーヌ(4歳メス)
- **Event currency / drops:** ティータイムコイン / ティータイムコイン【滅】 / 復刻コイン
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** スターオーシャン5発売日記念ピックアップキャラガチャ / ピックアップキャラガチャ（マリア） / ピックアップキャラガチャ（メイドのネル/メイドのクレア） / 新生活応援フェス(10連のみ、期間中1人1回)

#### `event_afl_40` — エイプリルフール2018 · PLAYABLE

- **About:** April Fools 2018: a doujin-sale parody (red book / green book), Koro Revorse.
- **Kind:** story; 3 missions; terms 2018-04-01 .. 2018-04-01 (1); recommended level up to 87
- **Story (2):** 赤い本と緑の本 / 完売は正義
- **Battles:** どーじん即売会
- **Difficulty tiers:** 超級
- **Bosses (hardest mission):** コロ・リヴォース / シマダの取り巻きＡ
- **Gachas opening alongside:** スターオーシャン5発売日記念ピックアップキャラガチャ

#### `event_ope_41` — オペラアルベルイベント · PLAYABLE

- **About:** Opera & Albel event: Albel vs Ashton, the three-eyed beauty, ruin exploration.
- **Kind:** story; 13 missions; terms 2018-04-12 .. 2020-04-09 (10); recommended level up to 200
- **Story (6):** アルベルＶＳアシュトン / ３つ目の美女 / 【航海日誌】争いの一因 / 【航海日誌】追う者、待つ者 / …
- **Battles:** 宝玉の守護者 / 村を目指して / 遺跡探索
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 食人樹 / クラウドベアド / ゲレル・ダディ / ゲレル・サン
- **Event currency / drops:** 財宝の銀貨 / 財宝の金貨 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(オペラ/黒将アルベル)

#### `event_eoe_14` — -- · BROKEN

- **About:** "eoe" crossover (partner not identified from master data): "star and gear meet"; Champ Peter boss; Energy Hexa drops.
- **Kind:** story; 8 missions; terms 2018-04-26 .. 2020-05-07 (3); recommended level up to 170
- **Story (2):** 星と歯車の出逢い / 輝け！ 天頂の星
- **Battles:** チャンプ・ペーター降臨
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** チャンプ・ペーター
- **Event currency / drops:** エナジーヘキサ【赤】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップガチャ（渚のリーンベル/ヴァシュロン/ゼファー） / ピックアップキャラガチャ（リーンベル）

#### `event_mel_43` — メリクルルシフェルイベント · PLAYABLE

- **About:** Mirakle & Lucifer event: an eternal prison, time-warping beasts.
- **Kind:** story; 12 missions; terms 2018-05-17 .. 2020-04-16 (9); recommended level up to 200
- **Story (5):** 永劫からのいざない / 暴かれし永劫の牢獄 / 壁に穿つ楔 / 無限の書架の一冊 / …
- **Battles:** 時空を歪めし魔獣 / 牢獄の看守たち
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ブルトガング / カルディアノンゾルダ / ファイアコープス / 金の妖精
- **Event currency / drops:** エタニティーコイン / エタニティーコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(青春のメリクル/ルシフェル)

#### `event_rad_44` — -- · PLAYABLE

- **About:** Giant mud-snail (ジャンボタニシ) gag event; high ranks only; "rad" label, likely a radio-show tie-in.
- **Kind:** story; 5 missions; terms 2018-05-20 .. 2019-05-30 (3); recommended level up to 200
- **Story (2):** 海辺の既視感 / お百姓さんを守るためならば
- **Battles:** タニシかどうかは俺が決める
- **Difficulty tiers:** 滅級 獄級 絶級
- **Bosses (hardest mission):** ジャンボタニシの中身

#### `event_wed_17` — ウェディング前半 · BROKEN

- **About:** Wedding event, first half (2018): "who is your bride?" — life with Nel / Maria / Koro.
- **Kind:** story; 16 missions; terms 2018-05-31 .. 2021-05-06 (3); recommended level up to 160
- **Story (8):** あなたの花嫁は？ / 扉越しの攻防 ～コロの場合～ / コーヒータイム ～ネルの場合～ / 深夜の語らい ～マリアの場合～ / …
- **Battles:** ネルの待つ家へ / マリアの待つ家へ / 光る植物を求め / 決戦への備え / 襲いかかる脅威
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 超級
- **Bosses (hardest mission):** シスターファンゴ / ナイトメアウィング / メタルゴーレム / ホーンドタートル
- **Event currency / drops:** ブライトブロッサム【赤】 / ブライダルコイン【銀】 / 復刻コイン
- **Gachas opening alongside:** ウエディングイベント前編ボックスガチャ / ピックアップキャラガチャ(フェイト) / ピックアップキャラガチャ(花嫁マリア/花嫁ネル) / ピックアップキャラガチャ(花嫁レイミ/花婿フェイト)

#### `event_wed_19` — ウェディング後半 · BROKEN

- **About:** Wedding event, second half (2018): new life with Reesh / Rena; beast monarch.
- **Kind:** story; 15 missions; terms 2018-06-14 .. 2021-05-06 (3); recommended level up to 200
- **Story (6):** 新生活 ～リーシュの場合～ / 家事の秘訣 ～レナの場合～ / 彼女の出生 / 抗戦計画 / …
- **Battles:** リーシュの待つ家へ / レナの待つ家へ / 大軍勢襲来 / 最終決戦 / 神殿哨戒戦
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ビーストモナーク
- **Event currency / drops:** ブライトブロッサム【黄】 / ブライダルコイン【金】 / 復刻コイン
- **Gachas opening alongside:** ウエディングイベント後編ボックスガチャ / ピックアップキャラガチャ(ネル) / ピックアップキャラガチャ(花嫁クレア/花嫁プリシス) / ピックアップキャラガチャ(花嫁レナ/花嫁イヴリーシュ)

#### `event_ill_47` — イラストコンテスト · PLAYABLE

- **About:** Illustration-contest event: winning fan illustrations as stories (Brunelli clinic, "beast kid" captain).
- **Kind:** story; 14 missions; terms 2018-06-28 .. 2021-05-20 (4); recommended level up to 200
- **Story (6):** 向学コラボレーション！ / 【航海日誌】ブルネリクリニック / 爆誕ヒーロー！ / 【航海日誌】自警団結成！ / …
- **Battles:** 宇宙海賊の撃退 / 機獣船長・ビーストキッド / 爆！機獣船長・ビーストキッド / 発明の資材調達
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 金の妖精 / 宇宙海賊団・エリート団員 / 宇宙海賊団・団員 / 機獣船長・ビーストキッド
- **Event currency / drops:** ヒーローコイン / ヒーローコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(ナースフィオーレ/ヒーローベルダ) / ピックアップキャラガチャ(ミュリア)

#### `event_asp_48` — 灼炎のアシュトンイベント · PLAYABLE

- **About:** "Blazing Ashton" event: trouble at the mountain top (Metox), protect the girl.
- **Kind:** story; 14 missions; terms 2018-07-12 .. 2020-04-23 (8); recommended level up to 200
- **Story (6):** 異変は山頂にあり / ぬぐえぬ不信感 / 人のぬくもりに触れて / 未来のためのさよなら / …
- **Battles:** メトークス山への道 / 少女を守れ / 山頂の決闘 / 爆・山頂の決闘
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** チンケシーフ / エインシェントガーディアン / 金の妖精 / セイタンシルバー
- **Event currency / drops:** メトークスコイン / メトークスコイン【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(ヴィクトル) / ピックアップキャラガチャ(灼炎のアシュトン/ペリシー)

#### `event_maid_51` — メイドソフィア・執事レオン · BROKEN

- **About:** Maid Sophia / butler Leon event: a cat gathering, a dream-forest, a memory mansion.
- **Kind:** story; 13 missions; terms 2018-08-30 .. 2021-05-20 (5); recommended level up to 200
- **Story (6):** ネコの集会 / 夢幻の森の迷い猫 / 記憶の館 / わたしが望む刹那 / …
- **Battles:** 夢魔の本性 / 悪魔の館への道 / 魔法の森のさんぽ道
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 夢幻のファンガス / シスターファンゴ / ペリュトン / アルベロデアニマ
- **Event currency / drops:** 夢の国の銀貨 / 夢の国の銀貨【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(エマーソン) / ピックアップキャラガチャ（メイドのソフィア/執事のレオン） / プレミアムキャラガチャ

#### `event_yuin_52` — ユーインBSオペライベント · PLAYABLE

- **About:** Euin (Blue Sphere-style) opera event: sudden time-warp, self-producing, a missing friend.
- **Kind:** story; 14 missions; terms 2018-09-13 .. 2020-05-14 (6); recommended level up to 200
- **Story (6):** 時空転移は突然に / 【航海日誌】自分プロデュース / 行方不明の友人 / 本気の理由は恋？ / …
- **Battles:** 炭鉱の危険生物 / 爆・炭鉱の危険生物 / 街道沿いの敵生体 / 近隣の敵生体
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ディノサウルス / ホーンドタートル / サーベルタイガー / 金の妖精
- **Event currency / drops:** ダグリスの鉱石 / ダグリスの鉱石【滅】 / 復刻コイン
- **Gachas opening alongside:** ステップ3で★5武器確定ガチャ１(10連★4以上確定) / ステップ3で★5武器確定ガチャ２(10連★4以上確定) / ステップ3で★5武器確定ガチャ３(10連★5武器確定) / ピックアップキャラガチャ(リムル)

#### `event_casino_53` — カジノイベント · PLAYABLE

- **About:** Casino event with a world boss and big-hunt: emergency landing, casino troublemakers, colosseum beast; single-only dice mission.
- **Kind:** worldboss+bighunt+story; 21 missions; terms 2018-09-27 .. 2018-10-18 (1); recommended level up to 200
- **Story (5):** 緊急着陸の代償 / 打開の糸口 / 暴かれた秘密 / ゲームオーバー / …
- **Battles:** この手にダイスを[シングル専用] / カジノの厄介客 / コロッセオの獣 / コロッセオ最強の生物 / コロッセオ最強の生物（１） / コロッセオ最強の生物（２）
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** クリムゾン・チャリオット
- **Event currency / drops:** カジノチップのかけら【緑】 / カジノチップのかけら【赤】 / カジノチップのかけら【黄】
- **World boss:** クリムゾン・チャリオット討伐
- **Gachas opening alongside:** Ganbling Satellite～ウサギの逆襲～ ボックスガチャ1箱目 / Ganbling Satellite～ウサギの逆襲～ ボックスガチャ2箱目 / Ganbling Satellite～ウサギの逆襲～ ボックスガチャ3箱目 / カジノダイス【赤】ボックスガチャ

#### `event_eoe_42` — -- · BROKEN

- **About:** "eoe" crossover part 2 (partner not identified): a closed graveyard, two letters, a dam, Basel back-alleys; Cannon Daddy boss; Energy Hexa drops.
- **Kind:** story; 16 missions; terms 2018-10-11 .. 2020-05-07 (2); recommended level up to 200
- **Story (8):** 閉ざされた墓地 / ふたつの手紙 / アポイントメント / 適材適所 / …
- **Battles:** ダムへの道 / バーゼルの路地裏 / 爆破の準備 / 瓦礫の怪物
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** キャノンダディ
- **Event currency / drops:** エナジーヘキサ【青】 / エナジーヘキサ【黄】 / 復刻コイン
- **Gachas opening alongside:** End of Eternity ―Letters―　ボックスガチャ1箱目 / End of Eternity ―Letters―　ボックスガチャ2箱目 / End of Eternity ―Letters―　ボックスガチャ3箱目 / End of Eternity ―Letters―　ボックスガチャ4箱目

#### `event_wel_54` — BASウェルチイベント · PLAYABLE

- **About:** "BAS Welch" event: the genius-girl war, 99-round Welch challenge.
- **Kind:** story; 13 missions; terms 2018-10-11 .. 2020-05-21 (6); recommended level up to 200
- **Story (5):** 会わすな危険 / 天才美少女大戦争 / 逆転の最終決戦へ / 一時休戦？ / …
- **Battles:** ウェルチ場外乱闘 / ウェルチ最終決戦 / ウェルチ９９番勝負 / 爆・ウェルチ最終決戦
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** カノンドラグーン / サーベルタイガー / 食人樹 / ランドタートル
- **Event currency / drops:** 発明家ギルドの缶バッジ / ウェルチ・ラボの缶バッジ / 復刻コイン
- **Gachas opening alongside:** End of Eternity ―Letters―　ボックスガチャ1箱目 / End of Eternity ―Letters―　ボックスガチャ2箱目 / End of Eternity ―Letters―　ボックスガチャ3箱目 / End of Eternity ―Letters―　ボックスガチャ4箱目

#### `event_hal_55` — ハロウィン2018イベント · BROKEN

- **About:** Halloween 2018: a festival haunted by a giant spirit.
- **Kind:** story; 17 missions; terms 2018-10-25 .. 2021-05-20 (3); recommended level up to 200
- **Story (7):** 参加者募集中 / 隠された真意 / 巨霊の暴走 / 精一杯の笑顔で / …
- **Battles:** オバケ退治 / 爆・祭りを守れ / 祭りに現れた悪霊 / 祭りを守れ / 道中の獣
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** イミテーションゴースト / 金の妖精 / セイタンシルバー / スケルトンソルジャー
- **Event currency / drops:** おばけクッキー / おばけオニグモクッキー / 復刻コイン
- **Gachas opening alongside:** ハロウィンボックスガチャ１箱目 / ハロウィンボックスガチャ２箱目 / ハロウィンボックスガチャ３箱目 / ハロウィンボックスガチャ４箱目（∞）

#### `event_max_38` — 覇級イベント · PLAYABLE

- **About:** Hegemon-rank (覇級) challenge: Michael of the Ten Wise Men.
- **Kind:** battle; 1 missions; terms 2018-10-25 .. 2021-06-22 (165); recommended level up to 300
- **Battles:** 十賢者ミカエル降臨
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** ミカエル
- **Gachas opening alongside:** ハロウィンボックスガチャ１箱目 / ハロウィンボックスガチャ２箱目 / ハロウィンボックスガチャ３箱目 / ハロウィンボックスガチャ４箱目（∞）

#### `event_aru_56` — エイルマットカーリンイベント · PLAYABLE

- **About:** Eilmat & Carlin event: guiding light, a reaper and a witch, usurper from the heavens.
- **Kind:** story; 14 missions; terms 2018-11-15 .. 2020-05-28 (6); recommended level up to 200
- **Story (6):** 導きの光 / 死神と魔女 / 天からの簒奪者 / 啓示の導きし末期 / …
- **Battles:** カルディアノンの残党 / 爆・神を騙る異形 / 砂漠の危険生物 / 神を騙る異形
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** キラーワスプ / サハリエル / 金の妖精 / セイタンシルバー
- **Event currency / drops:** カルディアノン・タグ / カルディアノン・タグ【滅】 / 復刻コイン
- **Gachas opening alongside:** ★5確定キャラガチャ / ピックアップキャラガチャ(フェイズ) / ピックアップキャラガチャ（エイルマット/カーリン）

#### `event_Xmas_57` — クリスマス2018イベント · BROKEN

- **About:** Christmas 2018: the planet of the deadly winter, a ritual to protect.
- **Kind:** story; 15 missions; terms 2018-12-13 .. 2021-05-20 (4); recommended level up to 200
- **Story (7):** 死の冬の星 / 銀麗の三重奏 / 【航海日誌】適材適所？ / 【航海日誌】守り人揃いて / …
- **Battles:** 儀式の素材調達 / 儀式の練習 / 儀式を妨げる者 / 爆・儀式を妨げる者
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ウィンターボタニカルビースト / ホーンドタートル / ペリュトン / トレント
- **Event currency / drops:** ツリーオーナメント / コロオーナメント / 復刻コイン
- **Gachas opening alongside:** ステップ3で★5武器確定ガチャ１(10連★4以上確定) / ステップ3で★5武器確定ガチャ２(10連★4以上確定) / ステップ3で★5武器確定ガチャ３(10連★5武器確定) / ピックアップガチャ(雪花レナ/聖夜クレア/雪空アシュトン)

#### `event_BossRush_33` — 逆襲の三巨頭 · PLAYABLE

- **About:** "Counterattack of the three giants": year-end 2018 boss rush (Evil Eye, Aqua Regia, Amber Princess).
- **Kind:** battle; 2 missions; terms 2018-12-27 .. 2018-12-31 (1); recommended level up to 170
- **Battles:** 逆襲の三巨頭
- **Difficulty tiers:** 滅級 獄級
- **Bosses (hardest mission):** イビルアイ系d / アクアレジア / アンバープリンセス / ビーストモナーク
- **Gachas opening alongside:** 「追臆の眠る墓標」ボックスガチャ１箱目 / 「追臆の眠る墓標」ボックスガチャ２箱目 / 「追臆の眠る墓標」ボックスガチャ３箱目 / 「追臆の眠る墓標」ボックスガチャ４箱目

#### `event_nier_36` — -- · PLAYABLE

- **About:** Large crossover (73 missions, Dec 2018): "stone tablets of remembrance" with Emerson / Phase / Fayt / Marvel chapters; concurrent box gacha "追臆の眠る墓標" — likely the NieR:Automata collaboration.
- **Kind:** story; 73 missions; terms 2018-12-27 .. 2019-01-10 (1); recommended level up to 200
- **Story (8):** 追臆の石板 / 【エマーソン編】戦場の掟 / 【マーヴェル編】契約の対価 / 【レナ編】惨劇の紅涙 / …
- **Battles:** いにしえの兵器 / 氷塊の宝物庫への道（１） / 氷塊の宝物庫への道（２） / 氷塊の宝物庫への道（３） / 氷塊の宝物庫への道（４） / 氷塊の宝物庫への道（５）
- **Difficulty tiers:** エマーソン編 フェイズ編 フェイト編 マーヴェル編 レナ編 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** サンドイーター / アルベロデアニマ / アドミニスタードギア / 金の妖精
- **Event currency / drops:** 復刻コイン / 復刻コイン【滅】
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** 「追臆の眠る墓標」ボックスガチャ１箱目 / 「追臆の眠る墓標」ボックスガチャ２箱目 / 「追臆の眠る墓標」ボックスガチャ３箱目 / 「追臆の眠る墓標」ボックスガチャ４箱目

#### `event_xmas_31` — クリスマスイベント · BROKEN

- **About:** Christmas event (rerun): a worried Santa, recover the first star.
- **Kind:** story; 15 missions; terms 2018-12-27 .. 2021-05-06 (4); recommended level up to 200
- **Story (8):** 【航海日誌】悩むサンタクロース / 【航海日誌】潜入を試みる / 【航海日誌】あの娘に相談する / 【航海日誌】男は黙って正面突破 / …
- **Battles:** パーティーの準備 / 一番星を取り戻せ！
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** エメラルドドール / アースハイウィザード / 金の妖精 / セイタンシルバー
- **Event currency / drops:** クリスマスオーナメント / ベルオーナメント / 復刻コイン
- **Achievement tag:** 覚醒
- **Gachas opening alongside:** 「追臆の眠る墓標」ボックスガチャ１箱目 / 「追臆の眠る墓標」ボックスガチャ２箱目 / 「追臆の眠る墓標」ボックスガチャ３箱目 / 「追臆の眠る墓標」ボックスガチャ４箱目

#### `event_sak_60` — -- · BROKEN

- **About:** Crossover (Jan 2019), likely SAKURA WARS: a secret demon-exorcism squad, 降魔 (demons).
- **Kind:** story; 19 missions; terms 2019-01-17 .. 2020-04-23 (2); recommended level up to 200
- **Story (8):** 原生生物の異常行動 / 魔を祓う秘密部隊 / 受け継がれる遺志 / 宿した力の使い方 / …
- **Battles:** 妖気を目指して / 爆・降魔を討て / 猛る原生生物１ / 猛る原生生物２ / 猛る原生生物３ / 猛る原生生物４
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 金の妖精 / セイタンシルバー / ストーンゴーレム / ホーンドタートル
- **Event currency / drops:** 帝国華撃団コイン / 巴里華撃団コイン / 復刻コイン
- **Gachas opening alongside:** ステップ3で★5武器確定ガチャ１(10連★4以上確定) / ステップ3で★5武器確定ガチャ２(10連★4以上確定) / ステップ3で★5武器確定ガチャ３(10連★5武器確定) / ピックアップキャラガチャ(さくら/エリカ/ジェミニ)

#### `event_valentine_61` — バレンタイン2019イベント · PLAYABLE

- **About:** Valentine 2019: maidens on alert, cooking simulator, lake guardian.
- **Kind:** story; 15 missions; terms 2019-02-01 .. 2021-06-03 (4); recommended level up to 200
- **Story (7):** 乙女は臨戦態勢 / 狐の手も借りたい / 仕上げのおつかい / ハートフルしっぽ / …
- **Battles:** バレンタインの素材探し / 料理シミュレーター / 湖畔の番人 / 爆・湖畔の番人
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** キラーワスプ / スケレッテ・デ・ショコラ / 金の妖精 / ホーンドタートル
- **Event currency / drops:** バーニィのちょこっとチョコ / バーニィのたっぷりチョコ / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(甘狐のカーリン/天真のペリシー) / 復刻ﾋﾟｯｸｱｯﾌﾟ(甘猫のレナ/夢想のウェルチ/純愛のベルダ） / 贈り物に込めた想いボックスガチャ１箱目 / 贈り物に込めた想いボックスガチャ２箱目

#### `event_valcahenri_62` — ヴァルカアンリイベント · PLAYABLE

- **About:** Valka & Henri event: led by a stone of the abyss, invaders, loneliness.
- **Kind:** story; 15 missions; terms 2019-02-14 .. 2020-06-04 (5); recommended level up to 200
- **Story (7):** 深淵の石に導かれて / 侵略する者 / 孤独の闇 / モーフィスの輝き / …
- **Battles:** 心を蝕む闇 / 爆・心を蝕む闇 / 突入開始 / 襲い来るカルディアノン
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ジャンクワーカー / ブラスドラゴン / 金の妖精 / セイタンシルバー
- **Event currency / drops:** カルディアノンチップ / カルディアノンチップ【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(ヴァルカ/アンリ/バッカス) / 定常武器ガチャ【遠距離】【ライフル/ランチャー】 / 定常武器ガチャ【遠距離】【銃/弓/ダガー】

#### `event_shingeki_63` — -- · BROKEN

- **About:** ATTACK ON TITAN collaboration: expedition outside the walls, city defence, the rampaging (Eren) Titan; Survey Corps insignia.
- **Kind:** story; 22 missions; terms 2019-02-28 .. 2019-03-14 (1); recommended level up to 200
- **Story (11):** 壁外調査 / 母子の行方 / 伝説の天使 / 紋章都市の謎 / …
- **Battles:** 天使の眠る神殿へ / 市街地防衛戦 / 暴走する巨人 / 爆・暴走する巨人 / 街の警備 / 街までの護衛
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** エレン巨人
- **Event currency / drops:** 訓練兵団記章 / 調査兵団記章
- **Gachas opening alongside:** スターオーシャン3発売日記念ピックアップキャラガチャ / ステップ3で★5武器確定ガチャ１(10連★4以上確定) / ステップ3で★5武器確定ガチャ２(10連★4以上確定) / ステップ3で★5武器確定ガチャ３(10連★5武器確定)

#### `event_afl2019_65` — エイプリルフール2019 · PLAYABLE

- **About:** April Fools 2019: "SHIMA OCEAN – FAKE JAGA" parody, "well-done" difficulty, fake Sahariel.
- **Kind:** story; 4 missions; terms 2019-04-01 .. 2019-04-01 (1); recommended level up to 60
- **Story (3):** 未知の物質の調査 / 史上最高の英雄 / いつでもそばに
- **Battles:** 未曾有の強敵[シングル専用]
- **Difficulty tiers:** ウェルダン級
- **Bosses (hardest mission):** サハリエル？
- **Gachas opening alongside:** 「SHIMA　OCEAN　－FAKE　JAGA－」（エイプリルフールシマダボックスガチャ） / スターオーシャン5発売日記念ピックアップキャラガチャ

#### `event_tic_67` — 大人ティカ・リカルドイベント · PLAYABLE

- **About:** Adult Tika & Ricardo event: experiment's price, brother and sister, a crest of destruction.
- **Kind:** story; 14 missions; terms 2019-04-11 .. 2020-06-11 (4); recommended level up to 200
- **Story (6):** 実験の代償 / 兄と妹 / 破壊の紋章 / 過ぎた力の末路 / …
- **Battles:** 徘徊する獣 / 最奥を目指して / 爆・紋章が創りし怪物 / 紋章が創りし怪物
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Event currency / drops:** カバー付きカードキー / カバー付きカードキー【滅】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(刻星のティカ/リカルド)

#### `event_Guilty_70` — -- · PLAYABLE

- **About:** GUILTY GEAR collaboration part 1: star-eating stone, the Cube's castle, "GIVE AND TAKE".
- **Kind:** story; 20 missions; terms 2019-04-25 .. 2021-02-18 (2); recommended level up to 200
- **Story (9):** 星を食らう石 / 異界の破壊者 / ＧＩＶＥ ＡＮＤ ＴＡＫＥ / 心を持った兵器 / …
- **Battles:** キューブの居城 / 奪われる叡智 / 法力に代わる力 / 爆・奪われる叡智 / 突然の共闘 / 複製される生物
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ネフィル・ディアブロ / スティンガー / ゴーストオーナー / レオンブレード
- **Event currency / drops:** Ｍ．Ｏ．Ｍメダル【小】 / Ｍ．Ｏ．Ｍメダル【大】 / 復刻コイン
- **Gachas opening alongside:** 1周年レオンイベントボックスガチャ１箱目 / 1周年レオンイベントボックスガチャ２箱目 / 1周年レオンイベントボックスガチャ３箱目 / 1周年レオンイベントボックスガチャ４箱目

#### `event_OverRoad` — 覇王の挑戦 · PLAYABLE

- **About:** "The overlord's challenge" (覇王の挑戦): boss rush (Lucifer, Facula Dragon, Administered Gear).
- **Kind:** battle; 2 missions; terms 2019-05-01 .. 2019-05-09 (1); recommended level up to 170
- **Battles:** 覇王の挑戦
- **Difficulty tiers:** 滅級 絶級
- **Bosses (hardest mission):** ルシファー / ファキュラドラゴン / アドミニスタードギア
- **Gachas opening alongside:** EP2 CHAPTER：10 公開記念キャラガチャ / 静謐から零れし歯車たちボックスガチャ1(ギルティギアコラボ) / 静謐から零れし歯車たちボックスガチャ2(ギルティギアコラボ) / 静謐から零れし歯車たちボックスガチャ3(ギルティギアコラボ)

#### `event_Souffle_68` — スフレノエルイベント · PLAYABLE

- **About:** Souffle & Noel event: land defiled by demon stones, invaders from space.
- **Kind:** story; 14 missions; terms 2019-05-09 .. 2020-07-09 (4); recommended level up to 200
- **Story (6):** 魔の石に穢されし大地 / エルリアに集う者 / 宙からの浸食者 / 復興への祈り / …
- **Battles:** 哀しみの生存競争 / 村を侵す危険生物 / 爆・哀しみの生存競争 / 飢える生物
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Event currency / drops:** サーカスチケット【通常席】 / サーカスチケットＳ【特等席】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(スフレ/ノエル) / 週末１０連１回無料キャラガチャ

#### `event_radio2_69` — -- · PLAYABLE

- **About:** Mud-snail event 2: metal snail (Tanishi) hunting; likely the radio-show tie-in again.
- **Kind:** story; 7 missions; terms 2019-05-23 .. 2019-05-30 (1); recommended level up to 200
- **Story (4):** 狙うはタニシ / 輝きだすタニシ / タニシの正体 / タニシが導いた出会い
- **Battles:** タニシ発見 / 鋼のＴａＮｉＳｈｉ
- **Difficulty tiers:** 滅級 獄級 絶級
- **Event currency / drops:** Gメタルタニシの貝殻 / メタルタニシの貝殻
- **Gachas opening alongside:** ピックアップキャラガチャ(クレス/ミント) / 週末１０連１回無料キャラガチャ

#### `event_TOP_1_71` — -- · BROKEN

- **About:** TALES OF PHANTASIA collaboration part 1: return to Toltus (Cless / Mint); gels (グミ) as drops.
- **Kind:** story; 15 missions; terms 2019-05-25 .. 2020-11-05 (2); recommended level up to 200
- **Story (6):** 邂逅 / すれ違い / １つの月 / 石板と魔法陣 / …
- **Battles:** クール村への帰路 / 共闘 / 影が誘う巨躯 / 洞窟に潜む生物 / 爆・影が誘う巨躯
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** クリムゾンビースト
- **Event currency / drops:** アップルグミ / レモングミ / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(クレス/ミント) / 週末１０連１回無料キャラガチャ

#### `event_TOP_2_72` — -- · BROKEN

- **About:** TALES OF PHANTASIA collaboration part 2: temple, Dhaos's castle, the mad demon king (Shadow Dhaos).
- **Kind:** story; 17 missions; terms 2019-06-06 .. 2020-11-05 (2); recommended level up to 200
- **Story (8):** 世界を見つめる神殿 / 真実の瞳 / 降臨せし魔王の城 / 違和感 / …
- **Battles:** ダオス城突入 / 爆・狂気の魔王 / 狂気の魔王 / 神殿の試練 / 虚ろな生物
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** シャドウダオス
- **Event currency / drops:** オレンジグミ / パイングミ / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(アーチェ/チェスター) / 覚醒キャラピックアップガチャ(フィオーレ/フィア/サラ)

#### `event_sum_49` — 【180726】水着前半イベント · PLAYABLE

- **About:** Swimsuit event 2018 first half (rerun 2019): the sea is calling, a dragon-man in a sea cave.
- **Kind:** story; 14 missions; terms 2019-07-18 .. 2021-05-20 (3); recommended level up to 200
- **Story (6):** 海が呼んでいる / 綺麗な光にご用心？ / 結界の奥に…… / 紺碧なる海竜の末裔 / …
- **Battles:** ミリーの捜索 / 海岸での物資調達 / 海底洞窟の竜人 / 爆・海底洞窟の竜人
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** フロストツリー / アクアレジア / 海竜の長ドラコ / 海竜人
- **Event currency / drops:** 竜人コイン / 竜人コイン【滅】 / 復刻コイン
- **Gachas opening alongside:** サマーステップアップキャラガチャ第１弾 / スターオーシャン発売日記念ピックアップキャラガチャ / ピックアップキャラガチャ（真夏のネル/真夏のエッジ） / 紺碧なる海竜の末裔　ボックスガチャ1箱目

#### `event_sww2019_75` — 水着イベント2019前半 · PLAYABLE

- **About:** Swimsuit event 2019 first half: vacation, beach house, chasing the attacker.
- **Kind:** story; 15 missions; terms 2019-07-18 .. 2021-06-03 (3); recommended level up to 200
- **Story (7):** バカンスの事情 / 【航海日誌】今年も熱い海の家 / 追走、襲撃犯！ / 襲撃犯の素顔 / …
- **Battles:** 呼び出される魔物 / 爆・見覚えのある背中 / 襲撃犯の術 / 見覚えのある背中
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ウェービングシザー / 憤怒のアドレー / クリムゾン・ボイルドフィッシュ / ホーンドタートル
- **Event currency / drops:** ドリンクコースター / ドルフィンコースター / 復刻コイン
- **Gachas opening alongside:** サマーステップアップキャラガチャ第１弾 / スターオーシャン発売日記念ピックアップキャラガチャ / ピックアップキャラガチャ（真夏のネル/真夏のエッジ） / 紺碧なる海竜の末裔　ボックスガチャ1箱目

#### `event_sum_50` — 【180809】水着後半イベント · PLAYABLE

- **About:** Swimsuit event 2018 second half (rerun): the sea-god calamity.
- **Kind:** story; 15 missions; terms 2019-07-31 .. 2021-05-20 (3); recommended level up to 200
- **Story (7):** 贄を欲する災厄 / 荒ぶる海神を探して / 正体見たり / 海神の黙詩 / …
- **Battles:** 海底の捜索 / 災厄の元凶 / 爆・災厄の元凶
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ホーンドトータス / キラーシザース / サンドイーター / ディザスター・クラブ
- **Event currency / drops:** 海神の真珠 / 海神の黒真珠 / 復刻コイン
- **Gachas opening alongside:** サマーステップアップキャラガチャ第2弾 ステップ1 / サマーステップアップキャラガチャ第2弾 ステップ2 / サマーステップアップキャラガチャ第2弾 ステップ3 / サマーステップアップキャラガチャ第2弾 ステップ4

#### `event_sww2019_76` — 水着イベント2019後半 · PLAYABLE

- **About:** Swimsuit event 2019 second half: undersea temple, the flame that shakes the sea.
- **Kind:** story; 17 missions; terms 2019-07-31 .. 2021-06-03 (3); recommended level up to 200
- **Story (8):** 海中での異変 / 【航海日誌】スイカ割りの起源？ / 迷い子の憐憫 / 岐路に立ち / …
- **Battles:** 海中神殿に潜む影 / 爆・絶海を揺るがす炎 / 絶海を揺るがす炎 / 襲い来る魔物 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** スノウマーメイド / アイスコープス / 金の妖精 / セイタンシルバー
- **Event currency / drops:** 切り分けたスイカ / 割ったスイカ / 復刻コイン
- **Gachas opening alongside:** サマーステップアップキャラガチャ第2弾 ステップ1 / サマーステップアップキャラガチャ第2弾 ステップ2 / サマーステップアップキャラガチャ第2弾 ステップ3 / サマーステップアップキャラガチャ第2弾 ステップ4

#### `event_iracon_78` — 2019イラコンイベント · PLAYABLE

- **About:** 2019 illustration-contest event: Japanese-style treasure hunt, oiran procession.
- **Kind:** story; 15 missions; terms 2019-08-29 .. 2021-06-03 (3); recommended level up to 200
- **Story (6):** 呪われし宝と華やぐ和の娯楽 / 瑠璃とつつじ / 黄金像をその手に / 艶やかに舞いんしょう / …
- **Battles:** レッツ・宝探し！ / 困惑の花魁道中 / 欺瞞の咆哮 / 爆・欺瞞の咆哮 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ゴールドラゴニュート / スケルトンアーマー / キラーワスプ / アヴァローニ
- **Event currency / drops:** 黄金のコイン / 黄金のコイン【呪】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(花魁ミュリア/ハンターセリーヌ)

#### `event_bstr_79` — BSチサトレオンイベント · PLAYABLE

- **About:** Blue Sphere Chisato & Leon event: flower-field bird, farewell to a comrade.
- **Kind:** story; 15 missions; terms 2019-09-12 .. 2020-09-03 (2); recommended level up to 200
- **Story (6):** 旅立つ仲間へ / 絶景を目指して / 広がる風景 / 花々からの贈り物 / …
- **Battles:** 爆・花蝕の魔鳥 / 花畑を目指せ / 花蝕の魔鳥 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ＢＳチサトレオンボス素体用
- **Event currency / drops:** 風景写真 / 絶景写真 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(蒼星のチサト/蒼星のレオン） / 覚醒キャラピックアップガチャ(オペラ/メリクル/マーヴェル)

#### `event_maid_80` — 2019メイドイベント第三段 · PLAYABLE

- **About:** 2019 maid event part 3: novice maid's first job, the thirsting water spirit.
- **Kind:** story; 15 missions; terms 2019-09-26 .. 2021-06-03 (4); recommended level up to 200
- **Story (6):** かけだしメイド登場 / メイドの初仕事 / 汚れの元を探して / お仕置き・ご奉仕・ご褒美！ / …
- **Battles:** お仕事の始まり / 澄んだ水を求めて / 爆・飢渇の水妖 / 調査ポイントボーナスミッション / 飢渇の水妖
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ベイビーク / メタルシェルホーネット / シスターファンゴ / タイニーファンゴ
- **Event currency / drops:** クッキングコイン / クッキングコイン【暴】 / 復刻コイン
- **Gachas opening alongside:** 「ご主人様にお仕置きを」ボックスガチャ1箱目 / 「ご主人様にお仕置きを」ボックスガチャ2箱目 / 「ご主人様にお仕置きを」ボックスガチャ3箱目 / 【復刻】ピックアップキャラガチャ　メイド

#### `event_ticket_03` — チケットミッション · PLAYABLE

- **About:** Ticket missions (2019–): ingot / gear / thread missions with 5× drop and rare-spawn boosts.
- **Kind:** daily; 30 missions; terms 2019-09-26 .. 2030-05-31 (1); recommended level up to 60
- **Battles:** インゴットミッション / ギアミッション / スレッドミッション / ハンマーミッション / 経験値素材アタッカー / 経験値素材キャスター
- **Difficulty tiers:** ドロップ5倍！ レア出現率UP！
- **Bosses (hardest mission):** ハニービー / ホーンドタートル / スレッドビースト
- **Gachas opening alongside:** 「ご主人様にお仕置きを」ボックスガチャ1箱目 / 「ご主人様にお仕置きを」ボックスガチャ2箱目 / 「ご主人様にお仕置きを」ボックスガチャ3箱目 / 【復刻】ピックアップキャラガチャ　メイド

#### `event_PSNC1_81` — -- · PLAYABLE

- **About:** Crossover part 1 (Oct 2019, code PSNC; partner not identified from master data): exchange students, a lament over the demon sea.
- **Kind:** story; 16 missions; terms 2019-10-10 .. 2019-11-07 (1); recommended level up to 200
- **Story (6):** 彼らを呼ぶ声 / 留学生の日常 / 魔の海に響く嘆き / 鏡のおまじない / …
- **Battles:** カムバックミッション / 危うい航路 / 歌声に誘われ / 爆・船乗りを喰らう魔物 / 船乗りを喰らう魔物 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ゲレル・サン / スケルトンソルジャー / 簒奪の騎士 / ゲレル・マミー
- **Event currency / drops:** ブランクカード【青】 / ブランクカード【青・滅】 / ★５片手剣交換コイン
- **Gachas opening alongside:** 【復刻】ピックアップキャラガチャ　2017ハロウィン / オバケとお菓子とお祭りと ボックスガチャ1箱目 / オバケとお菓子とお祭りと ボックスガチャ2箱目 / オバケとお菓子とお祭りと ボックスガチャ3箱目

#### `event_PSNC2_82` — -- · BROKEN

- **About:** Crossover part 2 (code PSNC): an incoming call, "senpai", heartscape; Antenora core boss; blank-card drops.
- **Kind:** story; 21 missions; terms 2019-10-24 .. 2019-11-07 (1); recommended level up to 200
- **Story (9):** 着信 / 先輩は先輩 / 心の風景 / 心強き者たち / …
- **Battles:** カムバックミッション / 対峙する影 / 爆・対峙する影 / 調査ポイントボーナスミッション / 迫りくる脅威 / 過去を知る魔物
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** アンテノーラ・コア
- **Event currency / drops:** ブランクカード【赤】 / ブランクカード【赤・滅】 / ★５大剣交換コイン
- **Gachas opening alongside:** スーパーピックアップキャラガチャ(ナビ) / スーパーピックアップキャラガチャ(芳澤かすみ) / スーパーピックアップキャラガチャ(鏡宮のレナ) / ピックアップキャラガチャ(芳澤かすみ/ナビ/鏡宮のレナ)

#### `event_3year_85` — 3周年イベント · BROKEN

- **About:** 3rd-anniversary event: party goods sale, visits to Tika / Welda / Reesh.
- **Kind:** story; 20 missions; terms 2019-11-28 .. 2021-06-03 (3); recommended level up to 132
- **Story (10):** 格安！ パーティーグッズ！ / ありふれた終焉 / 想いが生み出す呪い / 追想の輪舞曲 / …
- **Battles:** ティカに会いに行こう / ベルダに会いに行こう / リーシュに会いに行こう / 爆・王妃の呪いを断て！ / 王城の秘密を探れ / 王妃の呪いを断て！
- **Difficulty tiers:** 1500 上級 中級 初級 獄級 航海日誌 超級
- **Bosses (hardest mission):** ヴァリアントアーミー / イビルアイ系e / セイタンシルバー / 金の妖精
- **Event currency / drops:** ヴィンテージシャンパン / 復刻コイン
- **Gachas opening alongside:** 3周年記念大還元ガチャ / ピックアップキャラガチャ（円舞曲のティカ/輪舞曲のベルダ） / 復刻アイドル2019ピックアップキャラガチャ / 迷える子犬と五人の歌姫（ミルキークインテット）」ボックスガチャ1箱目

#### `event_god_86` — 神級イベント · BROKEN

- **About:** God-rank (神級) ranking event: an EV-hall dungeon descending floor by floor; Crocell's counterattack; scored ranking (EvRank groups).
- **Kind:** god+ranking; 85 missions; terms 2019-11-28 .. 2021-06-24 (13); recommended level up to 400
- **Battles:** ペリュトンの巣[シングル専用] / 地下1階・EVホール / 地下2階・EVホール / 地下2階・東エリア１[シングル専用] / 地下2階・東エリア２[シングル専用] / 地下2階・東エリア３[シングル専用]
- **Difficulty tiers:** 上級 中級 初級 獄級 神級 絶級
- **Bosses (hardest mission):** 逆襲のクロセル
- **Event currency / drops:** クロセルの鱗 / ガブリエ・セレスタの羽根の欠片
- **Gachas opening alongside:** 3周年記念大還元ガチャ / ピックアップキャラガチャ（円舞曲のティカ/輪舞曲のベルダ） / 復刻アイドル2019ピックアップキャラガチャ / 迷える子犬と五人の歌姫（ミルキークインテット）」ボックスガチャ1箱目

#### `event_Xmas3_84` — クリスマスイベント2019 · BROKEN

- **About:** Christmas 2019: becoming Santa (Perisie's training), a rampaging robot.
- **Kind:** story; 15 missions; terms 2019-12-12 .. 2021-06-03 (3); recommended level up to 200
- **Story (6):** サンタさんになろう！ / ペリシーのサンタ修行 / 謎のロボット、大暴れ / とびっきりの贈り物 / …
- **Battles:** サンタ修行シミュレーション１ / サンタ修行シミュレーション２ / 爆・鹿角将軍の生誕 / 調査ポイントボーナスミッション / 鹿角将軍の生誕
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** メカギディオン / セイタンイエロー / セイタンブルー / セイタングリーン
- **Event currency / drops:** サンタソックス / あったかサンタソックス / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ（銀雪マリア/雪猫ペリシー） / 復刻クリスマス2018ピックアップキャラガチャ

#### `event_Bow_74` — 恒常ボーマンイベント · PLAYABLE

- **About:** Permanent Bowman event: a pharmacist's healing power, blue crystal.
- **Kind:** story; 13 missions; terms 2019-12-19 .. 2020-07-16 (2); recommended level up to 200
- **Story (5):** 【航海日誌】薬屋さんと癒しの力 / 煌めく青い水晶 / 言語学者の悲劇 / 禍つ赤い水晶 / …
- **Battles:** 洞窟に潜む魔物 / 無へと還す赤光 / 爆・無へと還す赤光 / 赤い水晶を目指して
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Event currency / drops:** 青い水晶のかけら / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** SO3メモリアルピックアップキャラガチャ / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ1 / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ2 / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ3

#### `event_erisu_77` — エリスヨシュアイベント · PLAYABLE

- **About:** Eris & Joshua event: a girl trapped in an ice world, ruins-guardian machines; investigation-point bonus missions.
- **Kind:** story; 18 missions; terms 2019-12-19 .. 2020-08-30 (2); recommended level up to 200
- **Story (9):** 氷界に囚われた少女 / 翼持つ少女を探して / 追求者と復讐者 / 仲間の言葉を支えに / …
- **Battles:** 爆・遺跡を守る機械 / 調査ポイントボーナスミッション / 遺跡に住み着いた魔物 / 遺跡を守る機械
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** テンプルガーダー
- **Event currency / drops:** 白雲の羽根 / 朝陽の羽根 / 復刻コイン
- **Gachas opening alongside:** SO3メモリアルピックアップキャラガチャ / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ1 / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ2 / クリスマスイベント2019　プレシャス・プレゼンツボックスガチャ3

#### `event_BossRush_2019` — チケットミッション · PLAYABLE

- **About:** Year-end 2019 boss rush "return of the champions" (Michael, Lucifer).
- **Kind:** battle; 2 missions; terms 2019-12-26 .. 2019-12-31 (1); recommended level up to 170
- **Battles:** 覇者の再臨
- **Difficulty tiers:** 滅級 絶級
- **Bosses (hardest mission):** ミカエル / ルシフェル / 金の妖精 / コロ・リヴォース
- **Gachas opening alongside:** 復刻VP PUガチャ(レナス/アーリィ/アリューゼ/メルティーナ) / 復刻VP PUガチャ(蒼穹のレナス/フレイ/レザード/シルメリア)

#### `event_newyear_59` — 正月&SRFイベント · PLAYABLE

- **About:** New Year & SRF event (2020): New Year greetings, mochi-pounding battles, rampaging mascot.
- **Kind:** story; 16 missions; terms 2020-01-06 .. 2021-06-03 (3); recommended level up to 200
- **Story (8):** 新年のあいさつに / 晴れ着とモチ / 身近な神への願い / 新たなボディ / …
- **Battles:** 戦うモチツキ / 暴走のマスコット / 爆・暴走のマスコット / 続・モチとの死闘
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 賀正合体アケマシテイオー / ユニコーンウルフ
- **Event currency / drops:** お年玉袋 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 2019正月「わたしたちの初詣」ボックスガチャ1 / 2019正月「わたしたちの初詣」ボックスガチャ2 / 2019正月「わたしたちの初詣」ボックスガチャ3 / 2020年正月　「改新の志」ボックスガチャ1

#### `event_Guilty_88` — -- · BROKEN

- **About:** GUILTY GEAR collaboration part 2: meeting a knight, the colosseum, phantom Sol.
- **Kind:** story; 17 missions; terms 2020-01-30 .. 2021-02-18 (2); recommended level up to 200
- **Story (7):** ある騎士との出会い / 闘技場へ / 騎士たちの信条 / 翼の少女 / …
- **Battles:** 少女に襲い掛かる脅威 / 平原での勝負 / 幻影の好敵手 / 爆・幻影の好敵手 / 調査ポイントボーナスミッション / 闘技場の機械兵
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** 幻体ソル / ソル / 宇宙海賊団・エリート団員 / ディノサウルス
- **Event currency / drops:** Ｍ．Ｏ．Ｍメダル【剣】 / Ｍ．Ｏ．Ｍメダル【王】 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ（カイ/ディズィー） / 復刻ギルティギアコラボPUガチャ（ソル/エルフェルト） / 復刻ギルティギアコラボピックアップ武器ガチャ / 静謐から零れし歯車たちボックスガチャ1(ギルティギアコラボ)

#### `event_Valentine_2020` — チョコレート・イン・ザ・ヘル · PLAYABLE

- **About:** "Chocolate in the hell" Valentine 2020 battle event; single-only "obligation chocolate hell".
- **Kind:** battle; 3 missions; terms 2020-02-13 .. 2020-03-05 (1); recommended level up to 87
- **Battles:** チョコレート・イン・ザ・ヘル / 義理チョコ地獄[シングル専用]
- **Difficulty tiers:** 本命 滅級 獄級
- **Bosses (hardest mission):** マウンテンマタンゴ / スケレッテ・デ・ショコラ
- **Event currency / drops:** ハートチョコレート白 / バーニィのたっぷりチョコ / コインチョコ【滅】
- **Gachas opening alongside:** ハートフルしっぽ　ボックスガチャ1 / ハートフルしっぽ　ボックスガチャ2 / ハートフルしっぽ　ボックスガチャ3 / ピックアップキャラガチャ（天翼のエリス/甘恋のミキ）

#### `event_spring_89` — 温泉イベント · FULL

- **About:** Hot-spring event with a world boss and big-hunt: a snow-country boy, a mischievous monster, the fungus king Yukitake.
- **Kind:** worldboss+bighunt+story; 24 missions; terms 2020-02-27 .. 2020-03-19 (1); recommended level up to 200
- **Story (8):** 雪国の男の子 / 温泉街到着？ / 悪戯好きの魔物 / 雪解けの魔術 / …
- **Battles:** フロストを探して / 大好きな街 / 大好きな街(１) / 大好きな街(２) / 大好きな街(３) / 桃源郷を求めて
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 妖菌王・ユキタケマル
- **Event currency / drops:** 特製温泉まんじゅう【湯】 / 温泉まんじゅう【紅】 / 温泉まんじゅう【白】
- **World boss:** 妖菌王・ユキタケマル討伐
- **Gachas opening alongside:** SO3発売日記念ガチャ / 「温泉と悪戯好きの雪の魔物」ボックスガチャ1 / 「温泉と悪戯好きの雪の魔物」ボックスガチャ2 / 「温泉と悪戯好きの雪の魔物」ボックスガチャ3

#### `event_sak_90` — -- · BROKEN

- **About:** SHIN SAKURA WARS collaboration: the Imperial Combat Revue (帝国華撃団), Hatsuho and Anastasia; demon dragon.
- **Kind:** story; 21 missions; terms 2020-03-26 .. 2020-04-23 (1); recommended level up to 200
- **Story (9):** その名は、帝国華撃団 / 忍び寄る魔の手 / 初穂とアナスタシアの絆 / あざみとクラリスの絆 / …
- **Battles:** 不死の術者 / 溢れ出す魔物 / 爆・不死の術者 / 術者のラボを探して / 調査ポイントボーナスミッション / 降魔討伐ミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 降魔ドラゴン / レディ・ホーク / ホーンドタートル / エンシェントガード
- **Event currency / drops:** 初穂のブロマイド / あざみのブロマイド / クラリスのブロマイド
- **Gachas opening alongside:** PUキャラガチャ（天宮さくら/東雲初穂/クラリス） / スーパーピックアップキャラガチャ（クラリス） / スーパーピックアップキャラガチャ（天宮さくら） / スーパーピックアップキャラガチャ（東雲初穂）

#### `event_April2020` — エイプリルフール2020 · PLAYABLE

- **About:** April Fools 2020: a scary doll, secret job, Gerel apparition.
- **Kind:** story; 3 missions; terms 2020-04-01 .. 2020-04-01 (1); recommended level up to 30
- **Story (2):** 恐怖の人形 / 秘密のお仕事
- **Battles:** 溢れだすゲレルの怪
- **Difficulty tiers:** 初級
- **Gachas opening alongside:** SO5発売日記念ガチャ / 新サクラ大戦「星海に咲く新たなる花」ボックスガチャ1 / 新サクラ大戦「星海に咲く新たなる花」ボックスガチャ2 / 新サクラ大戦「星海に咲く新たなる花」ボックスガチャ3

#### `event_idol2_64` — アイドルイベント第二弾 · PLAYABLE

- **About:** Idol event part 2: vanished stars, audition preparation.
- **Kind:** story; 16 missions; terms 2020-04-16 .. 2021-06-03 (4); recommended level up to 200
- **Story (8):** 前回までのあらすじ / 消えた星々 / 星々への難路を進め / 暴走する想い / …
- **Battles:** オーディションの準備 / オーディションへの最終調整 / 妄念から解き放て / 爆・妄念から解き放て
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ヘッド・ブル / クール・ファン / パッション兵 / ハル
- **Event currency / drops:** デモテープ / デモテープ【滅】 / 復刻コイン
- **Gachas opening alongside:** 10連10ステップ目PU1体確定アイドル2018 ステップ1 / 10連10ステップ目PU1体確定アイドル2018 ステップ10 / 10連10ステップ目PU1体確定アイドル2018 ステップ2 / 10連10ステップ目PU1体確定アイドル2018 ステップ3

#### `event_idol_58` — アイドルイベント · PLAYABLE

- **About:** Idol event: a mega idol appears, first live, "beyond the top".
- **Kind:** story; 16 missions; terms 2020-04-16 .. 2021-05-20 (4); recommended level up to 200
- **Story (8):** 超大型アイドル、現る / 目には目を、ＩにはＩを / ファーストライブ / 夢と現実 / …
- **Battles:** 初お披露目 / 心機一転 / 爆・頂点を超えろ / 頂点を超えろ
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** すぴぴちゃん / 金の妖精 / セイタンシルバー / シスターファンゴ
- **Event currency / drops:** ファンレター / 熱烈なファンレター / 復刻コイン
- **Gachas opening alongside:** 10連10ステップ目PU1体確定アイドル2018 ステップ1 / 10連10ステップ目PU1体確定アイドル2018 ステップ10 / 10連10ステップ目PU1体確定アイドル2018 ステップ2 / 10連10ステップ目PU1体確定アイドル2018 ステップ3

#### `event_EP3CP1` — EP3CP1イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 1: Phantomized Synard hunt with investigation-point bonus missions.
- **Kind:** type3; 7 missions; terms 2020-04-30 .. 2021-06-17 (3); recommended level up to 200
- **Battles:** ファントマイズ・サイナード討伐 / 爆・ファントマイズ・サイナード討伐 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ファントマイズ・サイナード
- **Event currency / drops:** Ｐ・サイナードチップ / Ｐ・サイナードチップ【滅】 / 復刻コイン
- **Gachas opening alongside:** GWピックアップキャラガチャ 第一弾 / ピックアップキャラガチャ（狐将のカーリン/砲甲のリカルド）

#### `event_Memory_01` — 忘却の聖地ワドラム第1弾 · FULL

- **About:** "Wadorum, the Sanctuary of Oblivion" part 1: memory replays of Ratix / Edge.
- **Kind:** story; 11 missions; terms 2020-05-14 .. 2021-06-17 (2); recommended level up to 160
- **Story (5):** 忘却の聖地 / 記憶再生ラティクス編 / 記憶再生エッジ編 / 記憶再生レナ＆クロード編 / …
- **Battles:** 忘却の聖地ワドラム第1刻 / 爆・忘却の聖地ワドラム第1刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** 機獣船長・ビーストキッド / クリムドラゴン / ジエ・リヴォース / ナイトメアウィング
- **Event currency / drops:** 忘却のプレート / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップキャラガチャ（神翼のマリア/賢神のマスティマ） / ピックアップ武器ガチャ / １０連１０ステップ目ＰＵ１体確定 ステップ10\n（神翼のマリア/賢神のマスティマ） / １０連１０ステップ目ＰＵ１体確定 ステップ1\n（神翼のマリア/賢神のマスティマ）

#### `event_radiata_66` — ラジアータコラボ · PLAYABLE

- **About:** RADIATA STORIES collaboration: the green forest capital, the knight's name; Count Allocen.
- **Kind:** story; 17 missions; terms 2020-05-21 .. 2020-06-11 (1); recommended level up to 200
- **Story (9):** 緑森京にて / 神託のもつれ / 騎士の名乗り / 古の龍 / …
- **Battles:** アロケンの眷属 / 伯爵級アロケン / 爆・伯爵級アロケン / 龍の急襲
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** クリムドラゴン / サイレンスホーク / ダークドラゴネット / ディノサウルス
- **Event currency / drops:** 入隊案内 / 王国騎士団憲章 / 復刻コイン
- **Gachas opening alongside:** ロールピックアップキャラガチャ アタッカー / 復刻ラジアータ ストーリーズコラボPUキャラガチャ / 復刻ラジアータ ストーリーズコラボPU武器ガチャ / 週末限定ピックアップキャラガチャ

#### `event_kimono_91` — 着物鬼イベント · FULL

- **About:** Kimono & oni event: the doomed planet Ogas, the two-faced demon god.
- **Kind:** story; 15 missions; terms 2020-05-28 .. 2021-06-17 (2); recommended level up to 200
- **Story (6):** 滅びの惑星オーガス / 鬼の呪いか未聞の毒か / 鬼神再臨 / 鬼の夢跡 / …
- **Battles:** 二面の鬼神 / 爆・二面の鬼神 / 調査ポイントボーナスミッション / 鬼神の眷属
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** セイタンシルバー / アヴァローニ / ファイアコープス / イーヴルアイ
- **Event currency / drops:** 金方孔円銭 / 真方孔円銭 / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ(斬鬼のネル/鬼炎のアルベル)

#### `event_Bride2019_73` — 花嫁2019イベント · BROKEN

- **About:** Bride 2019 event: trouble from the island, the bond beyond the bridge; temple bird.
- **Kind:** story; 14 missions; terms 2020-06-04 .. 2021-06-03 (2); recommended level up to 200
- **Story (6):** 島からの異変 / あの橋を越えて / 変わらぬ絆 / 最高のパートナー / …
- **Battles:** 凶暴化した獣 / 爆・神殿に巣くう魔鳥 / 神殿に巣くう魔鳥 / 聖域に住む獣
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** ジャターユス / 食人樹 / ホーンドタートル / オキュペテ・ネクロマンシー
- **Event currency / drops:** 白愛の花 / 白愛の花【愛】 / 復刻コイン
- **Gachas opening alongside:** 10連10ステップ目PU1体確定花嫁2019 ステップ1 / 10連10ステップ目PU1体確定花嫁2019 ステップ10 / 10連10ステップ目PU1体確定花嫁2019 ステップ2 / 10連10ステップ目PU1体確定花嫁2019 ステップ3

#### `event_Memory_02` — 忘却の聖地ワドラム第2弾 · FULL

- **About:** Wadorum part 2: memory replays of Raffine / Bowman / Eris.
- **Kind:** story; 9 missions; terms 2020-06-11 .. 2021-06-17 (2); recommended level up to 160
- **Story (3):** 記憶再生ラフィネ編 / 記憶再生ボーマン編 / 記憶再生エリス編
- **Battles:** 忘却の聖地ワドラム第２刻 / 爆・忘却の聖地ワドラム第２刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** カノンドラグーン / ナイトエグザイル / スケレッテ・デ・ショコラ
- **Event currency / drops:** 忘却のプレート【02】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定花嫁2018 ステップ1 / 10連10ステップ目PU1体確定花嫁2018 ステップ10 / 10連10ステップ目PU1体確定花嫁2018 ステップ2 / 10連10ステップ目PU1体確定花嫁2018 ステップ3

#### `event_wed_45` — 花嫁前半 · PLAYABLE

- **About:** Bride event first half (42 missions): zombie outbreak waves.
- **Kind:** story; 42 missions; terms 2020-06-11 .. 2021-05-20 (2); recommended level up to 200
- **Story (14):** 命無き襲撃者 / 手掛かりを求めて / 進展のための対価 / 自己犠牲の代償 / …
- **Battles:** ゾンビとの遭遇戦 / ゾンビ大量発生（１） / ゾンビ大量発生（２） / ゾンビ大量発生（３） / 悲しみの妖屍鳥 / 植物大量発生（１）
- **Difficulty tiers:** 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** オキュペテ・ネクロマンシー / ゴーストオーナー
- **Event currency / drops:** 抗体【赤】 / 抗体【黄】 / 抗体【緑】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定花嫁2018 ステップ1 / 10連10ステップ目PU1体確定花嫁2018 ステップ10 / 10連10ステップ目PU1体確定花嫁2018 ステップ2 / 10連10ステップ目PU1体確定花嫁2018 ステップ3

#### `event_EP3CP2` — EP3CP2イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 2: Multiple Gear hunt.
- **Kind:** type3; 7 missions; terms 2020-06-25 .. 2021-06-17 (3); recommended level up to 200
- **Battles:** マルチプル・ギア討伐 / 爆・マルチプル・ギア討伐 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** マルチプル・ギア
- **Event currency / drops:** マルチプル・ギアチップ / マルチプル・ギアチップ【滅】 / 復刻コイン
- **Gachas opening alongside:** 3倍!スターピックアップキャラガチャ / ★５武器ガチャチケット / スフィア211キャラガチャ / スフィア211武器ガチャ

#### `event_VP2_92` — アリーシャルーファスイベント · PLAYABLE

- **About:** Alicia & Rufus (Valkyrie Profile: Lenneth / Covenant) event: the guard sword, the volcano cave lord.
- **Kind:** story; 15 missions; terms 2020-07-09 .. 2021-03-04 (2); recommended level up to 200
- **Story (6):** 光を放つ護身刀 / 竜穿の導き / それぞれの事情 / 王女の微笑み / …
- **Battles:** オーブの在処 / カルスタッドへ / 火山洞窟の主 / 爆・火山洞窟の主 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ラヴァゴーレム
- **Event currency / drops:** 魔晶石【希】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 3倍!スターピックアップキャラガチャ / VPピックアップ武器ガチャ / ピックアップキャラガチャ（アリーシャ/ルーファス） / 復刻VP PUガチャ(蒼穹のレナス/フレイ/レザード/シルメリア)

#### `event_sww2020_93` — 水着イベント2020 · FULL

- **About:** Swimsuit event 2020: a phantom beach, beach sports, "dream Rena".
- **Kind:** story; 26 missions; terms 2020-07-30 .. 2021-06-17 (2); recommended level up to 200
- **Story (8):** 星海に現れし渚 / 夢に見たバカンス / 襲い来る水着 / 夢の渚をもう少し / …
- **Battles:** ひと夏の幻 / ビーチスポーツ？ / 夢の渚のレナ？ / 常夏のシミュレーター / 渚のシミュレーター / 渚（？）のシミュレーター
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** アクアレジア / ディザスター・クラブ / ゲレル・サン / 真夏の幻影・レナ
- **Event currency / drops:** 人魚バーニィシール / 真夏の朱花 / 人魚バーニィシールＳＲ
- **Gachas opening alongside:** SO2発売日記念ガチャ / ピックアップキャラガチャ(常夏のベルダ/常夏のクレア) / ロールピックアップキャラガチャ シューター / 海神の黙詩 ボックスガチャ1箱目

#### `event_EP3CP3` — EP3CP3イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 3: Phantom Commander hunt.
- **Kind:** type3; 7 missions; terms 2020-08-27 .. 2021-06-17 (2); recommended level up to 200
- **Battles:** ファントム・コマンダー討伐 / 爆・ファントム・コマンダー討伐 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ファントム・コマンダー
- **Event currency / drops:** ポップハートチップ / ハイポップハートチップ / 復刻コイン
- **Gachas opening alongside:** ピックアップキャラガチャ（渚のエリス/渚のラヴァーニア） / 水着3ピックアップ武器ガチャ / １０連１０ステップ目ＰＵ１体確定 ステップ10（渚のエリス/渚のラヴァーニア） / １０連１０ステップ目ＰＵ１体確定 ステップ1（渚のエリス/渚のラヴァーニア）

#### `event_Memory_03` — 忘却の聖地ワドラム第3弾 · FULL

- **About:** Wadorum part 3: memory replays of Farleen / Crowe / Dias.
- **Kind:** story; 9 missions; terms 2020-09-10 .. 2021-06-17 (2); recommended level up to 160
- **Story (3):** 記憶再生ファリン編 / 記憶再生クロウ編 / 記憶再生ディアス編
- **Battles:** 忘却の聖地ワドラム第３刻 / 爆・忘却の聖地ワドラム第３刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** アドミニスタードギア / パンプキンツリー / ランドクラーケン
- **Event currency / drops:** 忘却のプレート【03】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップキャラガチャ（神星のレナ） / ピックアップキャラガチャ（神翼のフェイト） / 神星ピックアップ武器ガチャ / １０連１０ステップ目ＰＵ１体確定 ステップ1(神星のレナ)

#### `event_Memory_04` — 忘却の聖地ワドラム第4弾 · FULL

- **About:** Wadorum part 4: memory replays of Anne / Ronyx / Precis.
- **Kind:** story; 9 missions; terms 2020-10-08 .. 2021-06-17 (2); recommended level up to 160
- **Story (3):** 記憶再生アンヌ編 / 記憶再生ロニキス編 / 記憶再生プリシス編
- **Battles:** 忘却の聖地ワドラム第４刻 / 爆・忘却の聖地ワドラム第４刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** クラブ系e / 皇玉蟲 / マザーバイラスポッド
- **Event currency / drops:** 忘却のプレート【04】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定メイド1 ステップ1 / 10連10ステップ目PU1体確定メイド1 ステップ10 / 10連10ステップ目PU1体確定メイド1 ステップ2 / 10連10ステップ目PU1体確定メイド1 ステップ3

#### `event_EP3CP4` — EP3CP4イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 4: the Phantoms' counterattack (Phantomized Armaros / Lucifer).
- **Kind:** type3; 7 missions; terms 2020-10-22 .. 2021-06-17 (2); recommended level up to 200
- **Battles:** 爆・逆襲のファントム / 調査ポイントボーナスミッション / 逆襲のファントム
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ファントマイズ・アルマロス / ファントマイズ・ルシフェル / ファントマイズ・サハリエル
- **Event currency / drops:** 奇術師バーニィクッキー / 吸血鬼バーニィクッキー / 復刻コイン
- **Gachas opening alongside:** ハロウィンボックスガチャ１箱目 / ハロウィンボックスガチャ２箱目 / ハロウィンボックスガチャ３箱目 / ハロウィンボックスガチャ４箱目（∞）

#### `event_FT2019_83` — ハロウィン2019（童話イベント） · BROKEN

- **About:** Halloween 2019 (fairy-tale event): guided into a storybook world — sweets witch, exorcist.
- **Kind:** story; 17 missions; terms 2020-11-05 .. 2021-06-03 (2); recommended level up to 200
- **Story (8):** おとぎの世界に導かれて / 『お菓子の魔女とおかしなお菓子』 / 『天と地獄とエクソシスト』 / 幻の幸せ / …
- **Battles:** お菓子が襲ってきた！ / 爆・虚夢へ誘う死神 / 虚夢へ誘う死神 / 調査ポイントボーナスミッション / 魔物が襲ってきた！
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 鎧兵士 / セイタンシルバー / 金の妖精 / 骸王・ナイトメアロード
- **Event currency / drops:** 破れた頁 / 童話本 / 復刻コイン
- **Gachas opening alongside:** 2019ハロウィンイベント ようこそ　夢と幻のおとぎ世界へ　ボックスガチャ1 / 2020ハロウィンイベント ようこそ　夢と幻のおとぎ世界へ　ボックスガチャ2 / 2021ハロウィンイベント ようこそ　夢と幻のおとぎ世界へ　ボックスガチャ3 / SO3メモリアルピックアップキャラガチャ

#### `event_Memory_05` — 忘却の聖地ワドラム第5弾 · FULL

- **About:** Wadorum part 5: memory replays of Lilia / Bacchus / Ernest.
- **Kind:** story; 9 missions; terms 2020-11-12 .. 2021-06-17 (2); recommended level up to 160
- **Story (3):** 記憶再生リリア編 / 記憶再生バッカス編 / 記憶再生エルネスト編
- **Battles:** 忘却の聖地ワドラム第５刻 / 爆・忘却の聖地ワドラム第５刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** エンシェントペリュトン / ネフィル・ディアブロ / ルシファー
- **Event currency / drops:** 忘却のプレート【05】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定　ステップ1(神龍のアシュトン) / 10連10ステップ目PU1体確定　ステップ10(神龍のアシュトン) / 10連10ステップ目PU1体確定　ステップ2(神龍のアシュトン) / 10連10ステップ目PU1体確定　ステップ3(神龍のアシュトン)

#### `event_4year_95` — 4周年イベント · FULL

- **About:** 4th-anniversary event: "Starverse" idol auditions, dance lessons, song-star simulator.
- **Kind:** story; 16 missions; terms 2020-11-26 .. 2021-06-17 (3); recommended level up to 200
- **Story (6):** 記憶の宙域 / スターバース挑戦 / なりきる技術 フェイト編 / アイドルの休息 レナ編 / …
- **Battles:** オーディション本番 / ダンスレッスン / 歌星シミュレーター / 爆・オーディション本番 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** 歌星ジヴェレーゼ / 歌星ベルダ / 歌星ソフィア・絶 / 歌星イヴリーシュ
- **Event currency / drops:** 歌星王子のピンバッジ / 歌星姫のピンバッジ / 復刻コイン
- **Gachas opening alongside:** 4周年記念ガチャ / ピックアップキャラガチャ(歌星レナ/歌星フェイト) / 復刻アイドル2018/10連10ステップ目PU1体確定　ステップ1 / 復刻アイドル2018/10連10ステップ目PU1体確定　ステップ10

#### `event_Memory_06` — 忘却の聖地ワドラム第6弾 · FULL

- **About:** Wadorum part 6: memory replays of Ted / Millie / Rimle.
- **Kind:** story; 9 missions; terms 2020-12-17 .. 2021-06-17 (2); recommended level up to 160
- **Story (3):** 記憶再生テッド編 / 記憶再生ミリー編 / 記憶再生リムル編
- **Battles:** 忘却の聖地ワドラム第６刻 / 爆・忘却の聖地ワドラム第６刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** クリムゾン・ダラーヴァ / ガーディアンビースト / ブレイジングデーモン
- **Event currency / drops:** 忘却のプレート【06】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップキャラガチャ(雪狐カーリン/聖夜ネル) / 復刻xmas2018/10連10ステップ目PU1体確定　ステップ1 / 復刻xmas2018/10連10ステップ目PU1体確定　ステップ10 / 復刻xmas2018/10連10ステップ目PU1体確定　ステップ2

#### `event_2020_max_01` — 覇級祭り · FULL

- **About:** Hegemon-rank festival day 1: Beast Kid captain; Hegemon coins.
- **Kind:** battle; 1 missions; terms 2020-12-28 .. 2020-12-31 (1); recommended level up to 300
- **Battles:** 機獣船長・ビーストキッド参上
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** 機獣船長・ビーストキッド
- **Event currency / drops:** 覇者のコイン
- **Gachas opening alongside:** 週末限定ピックアップキャラガチャ

#### `event_2020_max_02` — 覇級祭り · FULL

- **About:** Hegemon-rank festival day 2: Akemashite-O (New Year mecha); Hegemon coins.
- **Kind:** battle; 1 missions; terms 2020-12-31 .. 2021-01-03 (1); recommended level up to 300
- **Battles:** 賀正合体アケマシテイオー襲来
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** 賀正合体アケマシテイオー
- **Event currency / drops:** 覇者のコイン
- **Gachas opening alongside:** 2020年正月　「改新の志」ボックスガチャ1 / 2020年正月　「改新の志」ボックスガチャ2 / 2020年正月　「改新の志」ボックスガチャ3 / ピックアップキャラガチャ(初春ティカ/初夢ラヴァーニア)

#### `event_newyear_87` — 2020正月イベント · FULL

- **About:** New Year 2020 event: a year-long duel, the seer, a shrine; Daruma-izer boss.
- **Kind:** story; 16 missions; terms 2021-01-01 .. 2021-06-17 (2); recommended level up to 200
- **Story (7):** １年越しの決闘 / 未来を見通す者 / 巫の祠 / 変革の兆し / …
- **Battles:** 女神様ご一行 / 悪鬼との戦い / 爆・悪鬼との戦い / 策の綻び / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 航海日誌 超級
- **Bosses (hardest mission):** 招福絶倒ダルマイザー’５６
- **Event currency / drops:** コロだるま / コロだるま【滅】 / 復刻コイン
- **Gachas opening alongside:** 2020年正月　「改新の志」ボックスガチャ1 / 2020年正月　「改新の志」ボックスガチャ2 / 2020年正月　「改新の志」ボックスガチャ3 / ピックアップキャラガチャ(初春ティカ/初夢ラヴァーニア)

#### `event_newyear_88` — 正月イベント2021 · FULL

- **About:** New Year 2021 event: first dreams, endless calligraphy, kite racing.
- **Kind:** story; 15 missions; terms 2021-01-01 .. 2021-06-24 (2); recommended level up to 200
- **Story (6):** 初夢みるなら / エンドレス、書き初め / 凧、凧、走れ / 幸運のしるし / …
- **Battles:** 初夢の乱暴者 / 初夢の徘徊者 / 初夢の略奪者 / 爆・初夢の略奪者 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** ゴーストオーナー / ディノサウルス / クリムゾン・ボイルドフィッシュ / スノウマーメイド
- **Event currency / drops:** 海賊のお年玉袋 / レコロのお年玉袋 / 復刻コイン
- **Gachas opening alongside:** 2020年正月　「改新の志」ボックスガチャ1 / 2020年正月　「改新の志」ボックスガチャ2 / 2020年正月　「改新の志」ボックスガチャ3 / ピックアップキャラガチャ(初春ティカ/初夢ラヴァーニア)

#### `event_2020_max_03` — 覇級祭り · FULL

- **About:** Hegemon-rank festival day 3: Facula Dragon; Hegemon coins.
- **Kind:** battle; 1 missions; terms 2021-01-03 .. 2021-01-06 (1); recommended level up to 300
- **Battles:** ファキュラドラゴン襲来
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** ファキュラドラゴン
- **Event currency / drops:** 覇者のコイン
- **Gachas opening alongside:** 2020年正月　「改新の志」ボックスガチャ1 / 2020年正月　「改新の志」ボックスガチャ2 / 2020年正月　「改新の志」ボックスガチャ3 / ピックアップキャラガチャ(初春ティカ/初夢ラヴァーニア)

#### `event_2020_max_04` — 覇級祭り · FULL

- **About:** Hegemon-rank festival day 4: Wrathful Adray; Hegemon coins.
- **Kind:** battle; 1 missions; terms 2021-01-06 .. 2021-01-07 (1); recommended level up to 300
- **Battles:** 憤怒のアドレー襲来
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** 憤怒のアドレー
- **Event currency / drops:** 覇者のコイン
- **Gachas opening alongside:** 2019正月「わたしたちの初詣」ボックスガチャ1 / 2019正月「わたしたちの初詣」ボックスガチャ2 / 2019正月「わたしたちの初詣」ボックスガチャ3 / 2021年正月イベント　夢魔の初夢語り　ボックス1

#### `event_Memory_07` — 忘却の聖地ワドラム第7弾 · FULL

- **About:** Wadorum part 7: memory replays of Mirakle / Pavine / Mirage.
- **Kind:** story; 9 missions; terms 2021-01-14 .. 2021-06-24 (2); recommended level up to 160
- **Story (3):** 記憶再生メリクル編 / 記憶再生パヴィヌ編 / 記憶再生ミラージュ編
- **Battles:** 忘却の聖地ワドラム第７刻 / 爆・忘却の聖地ワドラム第７刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** アドヒジョン・アルマ / ゴールドラゴニュート / 夢幻のファンガス
- **Event currency / drops:** 忘却のプレート【07】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定　ステップ1(神弓のレイミ) / 10連10ステップ目PU1体確定　ステップ10(神弓のレイミ) / 10連10ステップ目PU1体確定　ステップ2(神弓のレイミ) / 10連10ステップ目PU1体確定　ステップ3(神弓のレイミ)

#### `event_EP3CP5` — EP3CP5イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 5: Asmodeus descends.
- **Kind:** type3; 7 missions; terms 2021-01-28 .. 2021-06-24 (2); recommended level up to 200
- **Battles:** アスモデウス降臨 / 爆・アスモデウス降臨 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** アスモデウス
- **Event currency / drops:** ラーザ宇宙軍チップ / ラーザ宇宙軍レアチップ / 復刻コイン
- **Gachas opening alongside:** 2020ギルティギアコラボ2　「分かたれた翼と迅雷の結び手」ボックスガチャ1 / 2020ギルティギアコラボ2　「分かたれた翼と迅雷の結び手」ボックスガチャ2 / 2020ギルティギアコラボ2　「分かたれた翼と迅雷の結び手」ボックスガチャ3 / ピックアップキャラガチャ(甘恋のミリー/甘砲のプリシス)

#### `event_Memory_08` — 忘却の聖地ワドラム第8弾 · FULL

- **About:** Wadorum part 8: memory replays of Sarah / Marvel / Celine.
- **Kind:** story; 9 missions; terms 2021-02-10 .. 2021-06-24 (2); recommended level up to 160
- **Story (3):** 記憶再生サラ編 / 記憶再生マーヴェル編 / 記憶再生セリーヌ編
- **Battles:** 忘却の聖地ワドラム第８刻 / 爆・忘却の聖地ワドラム第８刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** 妖菌王・ユキタケマル / ルシフェル / ウィンターボタニカルビースト
- **Event currency / drops:** 忘却のプレート【08】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップキャラガチャ(粛清のフレイ/フレイア) / 復刻VP ピックアップキャラガチャ(アリーシャ/ルーファス) / 復刻VP ピックアップキャラガチャ1 / 戦乙女（VPイベント）ボックスガチャ１箱目

#### `event_VP_94` — VPヴァルキリーレザードイベント · BROKEN

- **About:** Valkyrie Profile Valkyrie & Lezard event: death and reincarnation, "that girl Alicia"; phantom Valkyrie.
- **Kind:** story; 18 missions; terms 2021-02-18 .. 2021-03-04 (1); recommended level up to 200
- **Story (8):** 死と転生 / 魂の記憶 / その少女アリーシャ / シルメリア・ヴァルキュリア / …
- **Battles:** アリアの軍勢 / 幻影のレザード / 幻影のヴァルキリー / 爆・幻影のヴァルキリー / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** 幻影のヴァルキリー
- **Event currency / drops:** 魔晶石【淡紅】 / 高魔晶石【淡紅】 / 復刻コイン
- **Gachas opening alongside:** SO4発売日記念ガチャ / VPレザードイベント「慰霊の星の転生者たち」ボックスガチャ1 / VPレザードイベント「慰霊の星の転生者たち」ボックスガチャ2 / VPレザードイベント「慰霊の星の転生者たち」ボックスガチャ3

#### `event_EP3CP6` — EP3CP6イベントミッション · FULL

- **About:** Episode 3 chapter-campaign missions 6: Imitate Satanail descends.
- **Kind:** type3; 7 missions; terms 2021-02-25 .. 2021-06-24 (2); recommended level up to 200
- **Battles:** イミテイト・サタナイル降臨 / 爆・イミテイト・サタナイル降臨 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** イミテイト・サタナイル
- **Event currency / drops:** バッシェン軍チップ / バッシェン軍レアチップ / 復刻コイン
- **Gachas opening alongside:** SO3発売日記念ガチャ / SO5メモリアルピックアップキャラガチャ / ピックアップキャラガチャ(ジャンヌ/ジヴェレーゼ) / 復刻春節2020/10連10ステップ目PU1体確定　ステップ1

#### `event_Memory_09` — 忘却の聖地ワドラム第9弾 · FULL

- **About:** Wadorum part 9: memory replays of Irene / Perisie / "???".
- **Kind:** story; 9 missions; terms 2021-03-11 .. 2021-06-24 (2); recommended level up to 160
- **Story (3):** 記憶再生イレーネ編 / 記憶再生ペリシー編 / 記憶再生？？？編
- **Battles:** 忘却の聖地ワドラム第９刻 / 爆・忘却の聖地ワドラム第９刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** テンプルガーダー / リオメ・ンスクナ / 憤怒のアドレー
- **Event currency / drops:** 忘却のプレート【09】
- **Gachas opening alongside:** 10連10ステップ目PU1体確定　ステップ1(神導のソフィア) / 10連10ステップ目PU1体確定　ステップ10(神導のソフィア) / 10連10ステップ目PU1体確定　ステップ2(神導のソフィア) / 10連10ステップ目PU1体確定　ステップ3(神導のソフィア)

#### `event_idol4_89` — アイドル第四弾 · FULL

- **About:** Idol event part 4: debut, festival showdown.
- **Kind:** story; 15 missions; terms 2021-03-25 .. 2021-06-24 (2); recommended level up to 200
- **Story (6):** 人気者の宿命 / わたしたち、デビューします！ / アイドルとして / 本当の居場所 / …
- **Battles:** フェス対決 / 暴走する想い / 爆・暴走する想い / 調査ポイントボーナスミッション / ２軍との対決
- **Difficulty tiers:** 1500 上級 中級 初級 滅級 獄級 絶級 超級
- **Bosses (hardest mission):** 金の妖精 / セイタンシルバー / 願望の傀儡ビーナス・カナボシ / ＧＮＧ４８メンバー・ルクバー
- **Event currency / drops:** アトラクティヴタイム / チアリングブロッサム / 復刻コイン
- **Gachas opening alongside:** お掃除、炊事にトラブル発生！？　ボックスガチャ1 / お掃除、炊事にトラブル発生！？　ボックスガチャ2 / お掃除、炊事にトラブル発生！？　ボックスガチャ3 / ピックアップキャラガチャ(歌星カーリン/歌星ティカ)

#### `event_Memory_10` — 忘却の聖地ワドラム第10弾 · FULL

- **About:** Wadorum part 10: memory replays of Roger / Tinek / Chisato.
- **Kind:** story; 9 missions; terms 2021-04-08 .. 2021-06-24 (2); recommended level up to 160
- **Story (3):** 記憶再生ロジャー編 / 記憶再生ティニーク編 / 記憶再生チサト編
- **Battles:** 忘却の聖地ワドラム第１０刻 / 爆・忘却の聖地ワドラム第１０刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** クラウドベアド / 機獣船長・ビーストキッド / ジャターユス
- **Event currency / drops:** 忘却のプレート【10】 / 復刻コイン / 復刻コイン【滅】
- **Gachas opening alongside:** ピックアップキャラガチャ(ロジャー/ティニーク) / ピックアップ武器ガチャ / 復刻狐将/砲甲2020/10連10ステップ目PU1体確定　ステップ1 / 復刻狐将/砲甲2020/10連10ステップ目PU1体確定　ステップ10

#### `event_Memory_Last` — 忘却の聖地ワドラム最終刻 · PLAYABLE

- **About:** Wadorum final chapter: footsteps, Welch's mystery, "pure-white bond"; Asmodeus.
- **Kind:** story; 17 missions; terms 2021-04-22 .. 2021-05-13 (1); recommended level up to 200
- **Story (10):** 足跡 / ウェルチの怪 / 純白の絆 / 夢の中の夏 / …
- **Battles:** 古鴉、子古鴉、ここ古鴉 / 忘却の聖地ワドラム最終刻 / 爆・忘却の聖地ワドラム最終刻 / 調査ポイントボーナスミッション
- **Difficulty tiers:** 1500 上級 滅級 獄級 絶級
- **Bosses (hardest mission):** アスモデウス
- **Event currency / drops:** 忘却のプレート【11】 / 忘却のレアプレート【11】
- **Gachas opening alongside:** 「壊れた支配者と囚われの王妃」常夏イベント後編ボックスガチャ１箱目 / 「壊れた支配者と囚われの王妃」常夏イベント後編ボックスガチャ２箱目 / ウエディングイベント前編ボックスガチャ / ウエディングイベント後編ボックスガチャ

#### `event_Sphere211_01` — 覇級イベント · PLAYABLE

- **About:** Hegemon-rank (覇級) boss rush tied to Sphere 211: very hard re-fights of story bosses (Adhesion Alma, Administered Gear, Armaros Depth, …).
- **Kind:** battle; 14 missions; terms – .. – (0); recommended level up to 300
- **Battles:** アドヒジョン・アルマ降臨 / アドミニスタードギア襲来 / アルマロス・デプス降臨 / ジエ・リヴォース降臨 / ナイトエグザイル襲来 / ファキュラドラゴン襲来
- **Difficulty tiers:** 覇級
- **Bosses (hardest mission):** ジエ・リヴォース

#### `event_evo_blue` — 青の進化素材ミッション · FULL

- **About:** Daily evolution-material missions, Shooter (blue) role; beginner/intermediate/advanced.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** 進化素材シューター
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** カルディアノンゾルダ / カルディアノンゲネラ / ジャンクワーカー

#### `event_evo_green` — 緑の進化素材ミッション · FULL

- **About:** Daily evolution-material missions, Healer (green) role; beginner/intermediate/advanced.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** 進化素材ヒーラー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** キラーシザース / シスターファンゴ / アルベロデアニマ

#### `event_evo_purple` — 紫の進化素材ミッション · FULL

- **About:** Daily evolution-material missions, Caster (purple) role; beginner/intermediate/advanced.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** 進化素材キャスター
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** 宇宙海賊団・エリート団員 / ブラスドラゴン / 食人樹

#### `event_evo_red` — 赤の進化素材ミッション · FULL

- **About:** Daily evolution-material missions, Attacker (red) role; beginner/intermediate/advanced.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** 進化素材アタッカー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** キラーシザース / ブルトガング / ゲレル・ダディ

#### `event_evo_yellow` — 黄の進化素材ミッション · FULL

- **About:** Daily evolution-material missions, Defender (yellow) role; beginner/intermediate/advanced.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** 進化素材ディフェンダー
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** ヴァリアントアーミー / ホーンドタートル / エンシェントガード

#### `event_kororin2018` — コロリンピック · PLAYABLE

- **About:** "Koro-lympics" (コロリンピック): a tournament-style battle event (qualifier → quarter-final → semi-final → final stages) hosted by the mascot Koro; final boss Jie Revorse.
- **Kind:** type3; 4 missions; terms – .. – (0); recommended level up to 50
- **Battles:** コロリンピック予選ステージ / コロリンピック決勝ステージ / コロリンピック準々決勝ステージ / コロリンピック準決勝ステージ
- **Bosses (hardest mission):** ジエ・リヴォース

#### `event_money` — 売却素材ミッション · FULL

- **About:** Daily "ingot" missions that drop sell-for-Fol materials.
- **Kind:** daily+weekly; 3 missions; terms – .. – (0); recommended level up to 50
- **Battles:** インゴットミッション
- **Difficulty tiers:** 上級 中級 初級
- **Bosses (hardest mission):** ゲレル・サン / ホーンドタートル / 金の妖精

## Sphere 211

Sphere 211 was the live endgame mode in 3.7.0, reached through the home screen's extra-dungeon button.

| season | index | opened | closed | ranking opened | ranking closed |
|---|---|---|---|---|---|
| 1961750864 | 1 | 2020-06-25 15:00:00 | 2020-07-16 13:59:59 | 2020-06-25 15:00:00 | 2020-07-16 14:59:59 |
| 3991183594 | 2 | 2020-07-16 15:00:00 | 2020-08-20 13:59:59 | 2020-07-16 15:00:00 | 2020-08-20 14:59:59 |
| 2598604924 | 3 | 2020-08-20 15:00:00 | 2020-09-17 13:59:59 | 2020-08-20 15:00:00 | 2020-09-17 14:59:59 |
| 75957727 | 4 | 2020-09-17 15:00:00 | 2020-10-15 13:59:59 | 2020-09-17 15:00:00 | 2020-10-15 14:59:59 |
| 1937782089 | 5 | 2020-10-15 15:00:00 | 2020-11-19 13:59:59 | 2020-10-15 15:00:00 | 2020-11-19 14:59:59 |
| 3934872819 | 6 | 2020-11-19 15:00:00 | 2020-12-17 13:59:59 | 2020-11-19 15:00:00 | 2020-12-17 14:59:59 |
| 2643350629 | 7 | 2020-12-17 15:00:00 | 2021-01-21 13:59:59 | 2020-12-17 15:00:00 | 2021-01-21 14:59:59 |
| 221334004 | 8 | 2021-01-21 15:00:00 | 2021-02-18 13:59:59 | 2021-01-21 15:00:00 | 2021-02-18 14:59:59 |
| 2050390370 | 9 | 2021-02-18 15:00:00 | 2021-03-18 13:59:59 | 2021-02-18 15:00:00 | 2021-03-18 14:59:59 |
| 2498141701 | 10 | 2021-03-18 15:00:00 | 2021-04-22 13:59:59 | 2021-03-18 15:00:00 | 2021-04-22 14:59:59 |
| 3823218323 | 11 | 2021-04-22 15:00:00 | 2021-05-20 13:59:59 | 2021-04-22 15:00:00 | 2021-05-20 14:59:59 |
| 2062090025 | 12 | 2021-05-20 15:00:00 | 2021-06-10 13:59:59 | 2021-05-20 15:00:00 | 2021-06-10 14:59:59 |
| 233820095 | 13 | 2021-06-10 15:00:00 | 2021-06-24 13:59:59 | 2021-06-10 15:00:00 | 2021-06-24 14:59:59 |

Floors: 312. Floor backgrounds: `00_bm0047_b01a_01` yes. Floor maps: `bm0047_b01a` yes.

Mission-box missions: 540 distinct; battle maps 71/80, enemy models 152/152. Missing maps: bg91_04 bg91_05 bg91_14 bg91_15 bg91_18 bm0012_b01a bm0016_b01a bm0023_b01a bm0026_b01a.

Table rows: `master_sphere211` 13, `master_sphere211_auto_member_select` 500, `master_sphere211_floor` 312, `master_sphere211_floor_asset` 2503, `master_sphere211_floor_asset_box` 124, `master_sphere211_floor_clear_present` 312, `master_sphere211_floor_transfer_level` 99, `master_sphere211_floor_transfer_rate` 321, `master_sphere211_mission_box` 1171, `master_sphere211_overwrite_enemy_level` 67, `master_sphere211_ranking_reward` 24, `master_sphere211_rental_bonus` 13, `master_sphere211_treasure` 312, `master_sphere211_treasure_contents` 1, `master_sphere211_treasure_streak_bonus` 12

## Tower

Note: the tower was already switched off in 3.7.0 (`CParameterUtility::IsOpenTowerMission` returns 0 in the 3.7.0 client). In the port it is an opt-in (see docs/client-changes.md).

| area | name | opened | closed | missions | banner | maps | enemies | missing |
|---|---|---|---|---|---|---|---|---|
| `tower_07` | 試練の塔８（知能） | 2017-03-09 | 2017-04-06 | 20 | – | 1/1 | 11/11 |  |
| `tower_03` | 試練の塔３（マヒ） | 2017-03-23 | 2030-02-23 | 15 | – | 1/1 | 8/8 |  |
| `tower_17` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_13` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_23` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_22` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_12` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_16` |  | 2020-06-18 | 2020-06-25 | 15 | yes | 1/1 | 7/7 |  |
| `tower_02` | 試練の塔２（凍結） | 2017-03-02 | 2030-02-23 | 15 | – | 1/1 | 7/7 |  |
| `tower_06` | 試練の塔６（防御） | 2017-09-14 | 2017-10-12 | 20 | – | 1/1 | 9/9 |  |
| `tower_14` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 12/12 |  |
| `tower_10` | 連撃の塔１０<連撃> | 2017-04-27 | 2017-05-25 | 20 | – | 1/1 | 10/10 |  |
| `tower_18` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 9/9 |  |
| `tower_08` | 試練の塔７（冒険者） | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_04` | 試練の塔４（封印） | 2017-04-13 | 2030-02-23 | 15 | – | 1/1 | 7/7 |  |
| `tower_24` |  | 2020-06-18 | 2020-06-25 | 15 | yes | 1/1 | 10/10 |  |
| `tower_20` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_21` |  | 2020-06-18 | 2020-06-25 | 15 | yes | 1/1 | 7/7 |  |
| `tower_25` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 11/11 |  |
| `tower_09` | 試練の塔９（力） | 2017-04-06 | 2017-05-04 | 20 | – | 1/1 | 10/10 |  |
| `tower_01` | 試練の塔１（毒） | 2017-02-23 | 2030-02-23 | 15 | – | 1/1 | 7/7 |  |
| `tower_05` | 試練の塔５（呪い） | 2017-05-04 | 2030-02-23 | 15 | – | 1/1 | 10/10 |  |
| `tower_11` | 連撃の塔１１<毒リニューアル> | 2020-06-18 | 2020-06-25 | 15 | yes | 1/1 | 7/7 |  |
| `tower_15` |  | 2020-06-18 | 2020-06-25 | 20 | yes | 1/1 | 10/10 |  |
| `tower_19` |  | 2020-06-18 | 2020-06-25 | 15 | yes | 1/1 | 8/8 |  |

## Banners and images by category

| category | present / total |
|---|---|
| event_area.bg_resource | 36/106 |
| event_area.banner | 50/140 |
| tower_area.banner | 16/16 |
| gacha.banner | 245/785 |
| gacha.image1-4 | 34/305 |
| gacha_image.pickup | 269/779 |
| banner(is_home=1) | 121/362 |
| banner(is_home=0) | 272/856 |
| banner(is_home=3) | 16/16 |
| banner(is_home=2) | 40/136 |
| banner_replace | 14/30 |
| login_bonus.banner_image | 9/62 |
| selectpart.img_resource | 3/3 |
| loading_message.image | 45/46 |
| expiration_information | 3/6 |
| guide_information | 140/285 |
| area.bg_resource | 11/11 |
| training_area.bg_resource | 1/1 |
| sphere211_floor.bg_resource | 1/1 |
| world_map_group_mission.loading_bg | 40/42 |
| world_boss.enemy_icon | 4/4 |

### Stand-ins found in the sources

Same-stem images that could replace a missing one (a `_256` copy, or the same name with another numeric suffix). Computed by rule, not listed by hand. A stand-in is only a candidate: a nearby number can be different content (e.g. `banner_event_chr_NNN` are different characters), so the events plan must decide per image family whether substitution is acceptable:

- event_area.bg_resource: `00_bm0035_b01a_01` → `00_bm0035_b01a_01_256`
- event_area.bg_resource: `banner_enemy_event_001` → `banner_enemy_event_000`
- event_area.bg_resource: `banner_enemy_event_002` → `banner_enemy_event_000`
- event_area.bg_resource: `banner_event_so2_002` → `banner_event_so2_001`
- event_area.bg_resource: `banner_event_so2_003` → `banner_event_so2_001`
- event_area.bg_resource: `banner_roleexAtk_002` → `banner_roleexAtk_001`
- event_area.bg_resource: `banner_roleexCas_002` → `banner_roleexCas_001`
- event_area.bg_resource: `banner_roleexDef_002` → `banner_roleexDef_001`
- event_area.bg_resource: `banner_roleexHel_002` → `banner_roleexHel_001`
- event_area.bg_resource: `banner_roleexShu_002` → `banner_roleexShu_001`
- event_area.bg_resource: `banner_ticket_event_001` → `banner_ticket_event_002`
- event_area.bg_resource: `bbg90_07_02` → `bbg90_07_01`
- event_area.bg_resource: `bbg91_01_02` → `bbg91_01_02_256`
- event_area.bg_resource: `bbg91_17_02` → `bbg91_17_01`
- event_area.banner: `20191128_event_001` → `20191128_event_003`
- event_area.banner: `banner_enemy_event_001` → `banner_enemy_event_000`
- event_area.banner: `banner_enemy_event_002` → `banner_enemy_event_000`
- event_area.banner: `banner_event_chr_042` → `banner_event_chr_044`
- event_area.banner: `banner_event_chr_043` → `banner_event_chr_044`
- event_area.banner: `banner_event_chr_045` → `banner_event_chr_044`
- event_area.banner: `banner_event_chr_046` → `banner_event_chr_044`
- event_area.banner: `banner_event_so2_002` → `banner_event_so2_001`
- event_area.banner: `banner_event_so2_003` → `banner_event_so2_001`
- gacha.banner: 58 missing images have a stand-in (see `--json`)
- gacha.image1-4: 54 missing images have a stand-in (see `--json`)
- gacha_image.pickup: 78 missing images have a stand-in (see `--json`)
- banner(is_home=1): 19 missing images have a stand-in (see `--json`)
- banner(is_home=0): 62 missing images have a stand-in (see `--json`)
- banner(is_home=2): `20191128_event_001` → `20191128_event_003`
- banner(is_home=2): `banner_enemy_event_001` → `banner_enemy_event_000`
- banner(is_home=2): `banner_enemy_event_002` → `banner_enemy_event_000`
- banner(is_home=2): `banner_event_chr_042` → `banner_event_chr_044`
- banner(is_home=2): `banner_event_chr_043` → `banner_event_chr_044`
- banner(is_home=2): `banner_event_chr_045` → `banner_event_chr_044`
- banner(is_home=2): `banner_event_chr_046` → `banner_event_chr_044`
- banner(is_home=2): `banner_event_so2_002` → `banner_event_so2_001`
- banner(is_home=2): `banner_event_so2_003` → `banner_event_so2_001`
- banner_replace: 3 missing images have a stand-in (see `--json`)
- login_bonus.banner_image: `20200220_campaign_001` → `20200220_campaign_003`
- login_bonus.banner_image: `20200820_campaign_002` → `20200820_campaign_001`
- login_bonus.banner_image: `banner_campaign_044` → `banner_campaign_045`
- login_bonus.banner_image: `banner_campaign_046` → `banner_campaign_045`
- login_bonus.banner_image: `banner_campaign_068` → `banner_campaign_070`
- loading_message.image: 1 missing images have a stand-in (see `--json`)
- guide_information: 29 missing images have a stand-in (see `--json`)

### Missing images per category

Full lists for the event, Sphere 211, tower, login-bonus and area categories; the other categories' lists are in the `--json` output.

<details><summary>event_area.bg_resource: 70 missing</summary>

`00_bm0016_b01a_01` `00_bm0023_b01a_01` `00_bm0026_b01a_01` `00_bm0031_b01a_01` `00_bm0032_b01a_06` `00_bm0035_b01a_01` `banner_enemy_event_001` `banner_enemy_event_002` `banner_event_chr_001` `banner_event_chr_002` `banner_event_chr_003` `banner_event_chr_004` `banner_event_chr_005` `banner_event_chr_006` `banner_event_chr_007` `banner_event_chr_008` `banner_event_chr_009` `banner_event_chr_012` `banner_event_chr_013` `banner_event_chr_014` `banner_event_chr_015` `banner_event_chr_016` `banner_event_chr_017` `banner_event_chr_018` `banner_event_chr_019` `banner_event_chr_020` `banner_event_chr_021` `banner_event_chr_023` `banner_event_chr_024` `banner_event_chr_025` `banner_event_chr_027` `banner_event_chr_030` `banner_event_chr_031` `banner_event_chr_034` `banner_event_chr_036` `banner_event_chr_037` `banner_event_chr_039` `banner_event_chr_041` `banner_event_newyear_001` `banner_event_newyear_002` `banner_event_so2_002` `banner_event_so2_003` `banner_event_so2_004` `banner_event_so3_001` `banner_event_so3_002` `banner_event_vp_002` `banner_event_vp_003` `banner_roleexAtk_002` `banner_roleexCas_002` `banner_roleexDef_002` `banner_roleexHel_002` `banner_roleexShu_002` `banner_ticket_event_001` `bbc01_02_02` `bbc01_03_01` `bbc02_01_01` `bbg90_07_02` `bbg91_01_02` `bbg91_08_01` `bbg91_09_01` `bbg91_10_02` `bbg91_14_02` `bbg91_15_02` `bbg91_16_01` `bbg91_17_02` `bbg91_18_02` `ebg0012_b01a_01` `ebg0018_b01a_01` `ebg0021_b01a_01` `hcg1001_b01a`
</details>

<details><summary>event_area.banner: 90 missing</summary>

`20181122_event_001` `20181129_event_001` `20181129_event_002` `20181129_event_004` `20181213_event_001` `20190101_event_001` `20190117_event_001` `20190131_event_001` `20190214_event_001` `20190228_event_001` `20190328_event_001` `20190328_event_002` `20190411_event_001` `20190425_event_001` `20190509_event_001` `20190523_event_001` `20190525_event_001` `20190606_event_001` `20190627_event_001` `20190711_event_001` `20190718_event_001` `20190731_event_001` `20190815_event_001` `20190829_event_001` `20190912_event_001` `20190926_event_001` `20191017_event_001` `20191031_event_001` `20191107_event_001` `20191128_event_001` `20191212_event_001` `20191226_event_001` `20200130_event_001` `20200220_event_001` `20200326_event_002` `20200409_event_001` `20200709_event_001` `20200924_event_002` `20210422_event_001` `banner_enemy_event_001` `banner_enemy_event_002` `banner_event_chr_001` `banner_event_chr_004` `banner_event_chr_007` `banner_event_chr_010` `banner_event_chr_022` `banner_event_chr_024` `banner_event_chr_026` `banner_event_chr_029` `banner_event_chr_032` `banner_event_chr_033` `banner_event_chr_035` `banner_event_chr_036` `banner_event_chr_037` `banner_event_chr_038` `banner_event_chr_039` `banner_event_chr_041` `banner_event_chr_042` `banner_event_chr_043` `banner_event_chr_045` `banner_event_chr_046` `banner_event_chr_047` `banner_event_chr_048` `banner_event_chr_049` `banner_event_chr_050` `banner_event_chr_051` `banner_event_chr_052` `banner_event_chr_054` `banner_event_chr_055` `banner_event_chr_056` `banner_event_chr_057` `banner_event_chr_059` `banner_event_chr_060` `banner_event_chr_061` `banner_event_chr_062` `banner_event_chr_063` `banner_event_chr_064` `banner_event_chr_065` `banner_event_chr_066` `banner_event_chr_067` `banner_event_chr_068` `banner_event_chr_069` `banner_event_so1_100` `banner_event_so2_002` `banner_event_so2_003` `banner_event_so3_001` `banner_event_so3_002` `banner_event_vp_002` `banner_gacha_pickup_role_0054` `banner_gacha_pickup_role_0056`
</details>

<details><summary>banner(is_home=2): 96 missing</summary>

`20181115_event_001` `20181122_event_001` `20181129_event_001` `20181129_event_002` `20181213_event_001` `20190101_event_001` `20190117_event_001` `20190131_event_001` `20190214_event_001` `20190228_event_001` `20190328_event_001` `20190328_event_002` `20190411_event_001` `20190425_event_001` `20190509_event_001` `20190523_event_001` `20190525_event_001` `20190606_event_001` `20190627_event_001` `20190711_event_001` `20190718_event_001` `20190731_event_001` `20190815_event_001` `20190829_event_001` `20190912_event_001` `20190926_event_001` `20191017_event_001` `20191031_event_001` `20191107_event_001` `20191128_event_001` `20191212_event_001` `20191226_event_001` `20200130_event_001` `20200130_weapon_001` `20200220_event_001` `20200326_event_002` `20200409_event_001` `20200709_event_001` `20200924_event_002` `20210422_event_001` `banner_enemy_event_001` `banner_enemy_event_002` `banner_event_chr_001` `banner_event_chr_004` `banner_event_chr_007` `banner_event_chr_010` `banner_event_chr_022` `banner_event_chr_024` `banner_event_chr_026` `banner_event_chr_029` `banner_event_chr_032` `banner_event_chr_033` `banner_event_chr_035` `banner_event_chr_035_100` `banner_event_chr_036` `banner_event_chr_037` `banner_event_chr_038` `banner_event_chr_038_100` `banner_event_chr_039` `banner_event_chr_041` `banner_event_chr_042` `banner_event_chr_043` `banner_event_chr_045` `banner_event_chr_046` `banner_event_chr_047` `banner_event_chr_048` `banner_event_chr_049` `banner_event_chr_050` `banner_event_chr_050_100` `banner_event_chr_051` `banner_event_chr_052` `banner_event_chr_054` `banner_event_chr_054_002` `banner_event_chr_055` `banner_event_chr_056` `banner_event_chr_057` `banner_event_chr_059` `banner_event_chr_060` `banner_event_chr_061` `banner_event_chr_062` `banner_event_chr_063` `banner_event_chr_064` `banner_event_chr_065` `banner_event_chr_066` `banner_event_chr_067` `banner_event_chr_068` `banner_event_chr_068_002` `banner_event_chr_069` `banner_event_so1_100` `banner_event_so2_002` `banner_event_so2_003` `banner_event_so3_001` `banner_event_so3_002` `banner_event_so3_100` `banner_event_so5_001_100` `banner_event_vp_002`
</details>

<details><summary>login_bonus.banner_image: 53 missing</summary>

`20181115_campaign_001` `20181227_campaign_001` `20190131_campaign_001` `20190228_campaign_001` `20190320_campaign_001` `20190425_campaign_002` `20190525_campaign_001` `20190627_campaign_001` `20190627_campaign_003` `20190808_campaign_001` `20190829_campaign_001` `20191010_campaign_003` `20191128_campaign_001` `20191219_campaign_001` `20200130_campaign_001` `20200220_campaign_001` `20200319_campaign_001` `20200319_campaign_003` `20200416_campaign_001` `20200521_campaign_001` `20200709_campaign_001` `20200716_campaign_001` `20200820_campaign_002` `20201126_campaign_002` `banner_campaign_003` `banner_campaign_004` `banner_campaign_009` `banner_campaign_010` `banner_campaign_011` `banner_campaign_012` `banner_campaign_013` `banner_campaign_017` `banner_campaign_020` `banner_campaign_025` `banner_campaign_026` `banner_campaign_027` `banner_campaign_037` `banner_campaign_042` `banner_campaign_044` `banner_campaign_046` `banner_campaign_048` `banner_campaign_050` `banner_campaign_052` `banner_campaign_054` `banner_campaign_055` `banner_campaign_057` `banner_campaign_059` `banner_campaign_061` `banner_campaign_063` `banner_campaign_064` `banner_campaign_068` `banner_campaign_newyear_001` `banner_release_001`
</details>

<details><summary>world_map_group_mission.loading_bg: 2 missing</summary>

`bbc02_01_01` `bbg05_03_01`
</details>


### Banner-like images present but not referenced by master data (179)

Excluding `_256` copies of referenced images.

`00_bm0024_b01a_02` `00_bm0024_b01a_02_256` `00_bm0028_b01a_01` `00_bm0028_b01a_01_256` `00_bm0038_b01a_01` `00_bm0038_b01a_01_256` `00_bm0040_b01a_01` `00_bm0040_b01a_01_256` `00_bm0041_b01a_01` `00_bm0041_b01a_01_256` `00_bm0043_b01a_01` `00_bm0043_b01a_01_256` `00_bm0043_b01a_02` `00_bm0043_b01a_02_256` `00_bm0043_b01a_03` `00_bm0043_b01a_03_256` `00_bm0043_b01a_04` `00_bm0043_b01a_04_256` `00_bm0044_b01a_11` `00_bm0044_b01a_11_256` `00_bm0044_b01a_12` `00_bm0044_b01a_12_256` `00_bm0044_b01a_13` `00_bm0044_b01a_13_256` `00_bm0045_b01a_01` `00_bm0045_b01a_01_256` `00_bm0046_b01a_01` `00_bm0046_b01a_01_256` `00_bm0046_b02a_01` `00_bm0046_b02a_01_256` `00_bm0049_b01a_02` `00_bm0049_b01a_02_256` `00_bm0049_b01a_03` `00_bm0049_b01a_03_256` `00_bm0050_b02a_01` `00_bm0050_b02a_01_256` `00_bm0050_b03a_01` `00_bm0050_b03a_01_256` `00_bm0057_b01a_01` `00_bm0057_b01a_01_256` `20200206_campaign_001` `20200213_event_001` `20200220_campaign_003` `20200312_campaign_001` `20200521_event_001` `20200730_campaign_003` `20201022_chara_002` `banner_TrialSpace_001` `banner_TrialSpace_002` `banner_TrialSpace_003` `banner_TrialSpace_004` `banner_TrialSpace_005` `banner_TrialSpace_008_001` `banner_TrialSpace_013_001` `banner_TrialSpace_015_001` `banner_TrialSpace_018_001` `banner_TrialSpace_022_001` `banner_TrialSpace_025_001` `banner_campaign_045` `banner_closed_beta` `banner_premium_login` `banner_roleevoAtk_002` `banner_roleevoCas_002` `banner_roleevoDef_002` `banner_roleevoHel_002` `banner_roleevoShu_002` `bbg00_01_01` `bbg00_01_01_256` `bbg01_02_03` `bbg01_02_03_256` `bbg02_01_01` `bbg02_01_01_256` `bbg02_03_01` `bbg02_03_01_256` `bbg02_05_01` `bbg02_05_01_256` `bbg03_04_01` `bbg03_04_01_256` `bbg04_02_01` `bbg04_02_01_256` `bbg04_03_01` `bbg04_03_01_256` `bbg05_04_01` `bbg05_04_01_256` `bbg06_02_01` `bbg06_02_01_256` `bbg06_03_01` `bbg06_03_01_256` `bbg07_04_01` `bbg07_04_01_256` `bbg08_01_01` `bbg08_01_01_256` `bbg08_05_01` `bbg08_05_01_256` `bbg09_01_01` `bbg09_01_01_256` `bbg09_02_01` `bbg09_02_01_256` `bbg09_03_01` `bbg09_03_01_256` `bbg09_05_01` `bbg09_05_01_256` `bbg10_01_01` `bbg10_01_01_256` `bbg10_02_01` `bbg10_02_01_256` `bbg10_03_01` `bbg10_03_01_256` `bbg90_01_01` `bbg90_01_01_256` `bbg90_05_01` `bbg90_05_01_256` `bbg90_06_01` `bbg90_06_01_256` `bbg90_07_01` `bbg90_07_01_256` `bbg90_09_01` `bbg90_09_01_256` `bbg90_10_01` `bbg90_10_01_256` `bbg90_11_01` `bbg90_11_01_256` `bbg90_13_01` `bbg90_13_01_256` `bbg90_14_01` `bbg90_14_01_256` `bbg91_05_01` `bbg91_05_01_256` `bbg91_12_03` `bbg91_12_03_256` `bbg91_17_01` `bbg91_17_01_256` `bbg91_20_01_256` `bbg99_05_00` `bbg99_05_00_256` `bbg99_05_01` `bbg99_05_01_256` `bbg99_05_02` `bbg99_05_02_256` `bbg99_05_03` `bbg99_05_03_256` `bbg99_05_04` `bbg99_05_04_256` `bbg99_05_05` `bbg99_05_05_256` `bbg99_05_06` `bbg99_05_06_256` `bbg99_05_07` `bbg99_05_07_256` `bbg99_05_08` `bbg99_05_08_256` `bbg99_05_09` `bbg99_05_09_256` `bbg99_05_10` `bbg99_05_10_256` `bbg99_05_99` `bbg99_05_99_256` `bbg99_06_01` `bbg99_06_01_256` `bbg99_07_01` `bbg99_07_01_256` `ebg0005_b02a_01` `ebg0005_b02a_01_256` `ebg0007_b01a_02` `ebg0007_b01a_02_256` `ebg0014_b01b_01` `ebg0014_b01b_01_256` `ebg0014_b01f_01` `ebg0014_b01f_01_256` `ebg0014_b01h_01` `ebg0014_b01h_01_256` `ebg0014_b01i_01` `ebg0014_b01i_01_256` `ebg0014_b01j_01` `ebg0014_b01j_01_256` `ebg0015_b01a_02` `ebg0015_b01a_02_256` `ebg0019_b01a_01_256` `pickup_img_chara_007`
