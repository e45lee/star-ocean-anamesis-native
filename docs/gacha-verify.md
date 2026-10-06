# Gacha pick-ups vs banner images

Checks the reconstructed pick-ups of `data/gacha_pools.sqlite3` (`gacha_pickup`, built by
`tools/build_gacha_pools.py`, [server-rules.md 4.5](server-rules.md#gacha-pools)) against what the
3.7.0 banner images actually show. Reproduce with

```sh
tools/gacha_verify.py --master data/basmaster-3.7.0.sqlite3 --download work/download-3.7.0 \
    --out work/gacha-verify --report docs/gacha-verify.md      # ~1 min on 24 cores
```

It needs `opencv-python-headless` (in `requirements.txt`: `pip install -r requirements.txt` into
`.venv`) and `tools/aif2png`. Everything under `--out` (decoded images, features, contact sheets,
`results.json`) is derived game data and stays out of git. The part between the GENERATED markers
below is rewritten by the tool; the text around it is by hand (2026-10-05). Findings 1 and 2 below were
applied to the pools; the generated tables show the state after that.

## Method

- **Images.** Per gacha: the list banner (`master_gacha.banner_id` → `master_banner.image`,
  512×128), `image1..4` and the pick-up panels (`master_gacha_image`, 1024×512), decoded from
  `work/download-3.7.0/Image/etc2/*.aif` with `tools/aif2png` (via `tools/extract_banners.py`), with
  the APK's images as a fallback for names the download lacks (none of them is a gacha's banner or
  panel). 537 distinct images are present; 1,271 referenced names are not in the 3.7.0 data
  ([missing-assets-3.7.0.md](missing-assets-3.7.0.md); the stand-ins in `standin-assets/` are ours
  and are not used).
- **References.** Every `master_role` costume, keyed by its art key `<person>_b<NN><x>`
  (`master_person_id_label` up to the costume letter; rarity 5 and its rarity-6 evolution share it):
  the full illustration `<person>_fl<NN><x>` (alpha used as the keypoint mask) and the card art
  `_cs`: 634 illustrations of 322 costumes. Every pick-up and pool role has its illustration.
- **Detection.** The banners are composited from these very illustrations (scaled, cropped,
  overlapped, with effects), so this is same-source matching, not face recognition: OpenCV SIFT
  (RootSIFT descriptors), one FLANN index over all illustrations, Lowe's ratio test 0.75, matches
  grouped per illustration, then each candidate verified with a RANSAC similarity transform
  (`cv2.estimateAffinePartial2D`, scale 0.08–4), at least 15 % inliers, and overlapping weaker
  detections of another costume suppressed. List banners are upscaled 3× first. A detection is
  accepted at ≥ 8 inliers on a list banner and ≥ 10 on a panel.
- **OCR** was not used: tesseract isn't installed, and the art matching already identifies the
  costume, which the printed names (e.g. "★5メイドのネル") would only repeat. The texts were read by
  eye on the contact sheets of every mismatch below.
- **Comparison** per gacha, by art key: detected (union over its images) vs recorded (`gacha_pickup`
  roles; for boxes the role rows of `master_box_gacha`). Each detected character also gets the rank
  of this gacha's pools that holds it (S/A/B/C, `-` = in no pool: not drawable there at all).
- **Classes.** *confirmed*: same set. *missing from pickup*: a character on the banner is not
  recorded (also when nothing is recorded). *extra in pickup*: recorded, not on the banner; judged
  only when the images are complete (every image of the gacha present, or `pickup1`, the main panel
  that shows every pick-up), otherwise *inconclusive*, as is a banner where nothing was detected.
  *banner not available*: no image of the gacha survives. Weapon gachas aren't checked (the banners
  show weapons; 0 character detections on their 173 images serve as the negative control);
  permanent banners (R-PU-PERMANENT) and boxes only list what they show.

## Accuracy

Measured before trusting the rest (table below): on the 82 panels the master names
(`master_gacha_image.content_id`) every character is found and nothing else (82/82, +0); on the 173
weapon banners nothing is detected even at 6 inliers. The list banners are the weak case: recall
150/178 = 84 % at the threshold, with **no** wrong detection at any threshold, which is why an
*extra* is never judged from a list banner alone. On the main panels of R-PU-IMAGE gachas 63/65
recorded characters are found (64/66 with 6 "others" before the fixes, when EP2 CHAPTER:10 still
counted here); the 2 misses and 2 "others" are the EP2公開記念 panels (finding 6), a data finding
rather than a detector error. Every mismatch group below was checked by eye on its contact
sheet (the メモリアル reruns 0565 / 0590 / 0900 through the identical images of 0253 / 0255; of the
2017 step-ups one step per banner): every accepted detection is the character it names. Characters drawn very small in crowded group art (the 発売日記念
banners) can be missed, so their *extra* rows are flagged as probable only.

## Findings and what was done

Labels as in [server-rules.md](server-rules.md#labels). The first run (before the fixes) found 21
*missing*, 62 *extra* and 22 *both*. The user decided (2026-10-05): apply findings 1, 2 and 5 (all
R-PU-BANNERART in `tools/build_gacha_pools.py`, `data/gacha_pools.sqlite3` regenerated, 48 gachas
changed), and keep the over-broad pick-ups of findings 3, 4 and 6 as they are.

1. **Applied: featured units no rule recorded** (*missing from pickup*; the units were in no pool of
   these gachas, so they couldn't be drawn there at all). Now added to the pick-ups, and so to the S
   pool (R-PU-BANNERART "added units", `BANNER_ART_ADD`, (b)):
   - ホワイトデー限定復刻ピックアップキャラガチャ1 (2020-03-12): "この5キャラをピックアップ!" — 花婿フェイト,
     水着エッジ, Winter Fidel, 渚のラティクス, Blossom Dias. ガチャ2: 花婿クリフ, Vampire Victor, 雪空アシュトン,
     狼アルベル, 執事のレオン (male-only: "ガチャからは男性キャラのみ").
   - イヴリーシュ誕生日記念ガチャ (2020-12-24): "ピックアップは6人のイヴリーシュのみ!" — Bride Eve, 魔女,
     歌星, 迎春, 渚, 泉郷イヴリーシュ.
   - ステップアップシグムントガチャ1–3 (2017-11-20): "★5シグムント出現確率UP!!" — Sigmund (`cc0009_b01a`,
     collaboration); R-PU-NAME reads only bracketed names and "X確定".
   - EP2 CHAPTER:10 公開記念キャラガチャ (2019-05-01): "★5キャラクターはピックアップされているEP2キャラクター6人のみ";
     the master named only マスティマ. Added ウェルチ, ユーイン, カーリン, ヴァルカ (detected) and アンリ (the sixth
     figure, which the detector doesn't match; identified by eye against `cp0017_ic01a`). The master
     rates agree (a): S 6 %, A 0 %, so the ★5s of this gacha are its S pool.
   - 2018年福袋限定チケットガチャ(花嫁/水着/ハロウィンのみ): "花嫁、常夏、ハロウィン向けの11キャラ". R-PU-NAME
     matched only names containing 花嫁. Added the four 常夏 units (Miki, Sophia, Reimi, Myuria) and the
     three Halloween-2017 units (Devil Clair, Vampire Victor, Were-Millie); with the four brides released
     by then that makes the eleven (c: costume names). The brides released after the banner opened,
     which R-PU-NAME also finds, are kept (not narrowed).
   - Effect on the pools: their S pools are the pick-ups. Under R-SA-PICKUP, A is now every other
     general ★5. Before, it was the party roles only (R-SA-NOPICKUP), for ホワイトデー1/2 and シグムント1–3.
2. **Applied: R-PU-THEME read a part number as a year** (bug): `theme_pickups` turns a single digit
   after a theme word into 2016+N (documented for ハロウィンN only). "…PU1体確定メイド1" (2020-10-08, and
   復刻メイド1 2021-03-18, 20 gachas) became 2017 → no maid → R-PU-NEW → メイドレイミ / 執事エイルマット,
   while the banner ("復刻メイド") shows **★5メイドのクレア, ★5メイドのネル**; "メイド2" became 2018 → all four
   2018 maids, while the banner shows **執事のレオン, メイドのソフィア** only. Fix: `BANNER_ART` entries
   `メイド1` and `メイド2`, matched only when no digit follows (so `メイド2018` keeps its R-PU-THEME reading).
   `theme_pickups` checks the table before the digit reading, which stays as it is. 40 gachas changed;
   no other title has a theme word with a single digit (メイド3 is R-PU-IMAGE).
3. **Reviewed, kept: numbered halves of a seasonal rerun get the whole theme**: 復刻水着2018(1) shows
   渚のミリー + 渚のマリア, (2) 渚のラティクス + 渚のイヴリーシュ + 渚のレナ; both record all five (20 gachas).
4. **Reviewed, kept: メモリアル banners show a subset of the cast's limited units**: SO1/SO2/SO3/SO5
   メモリアル (2019-12 … 2021-05, 9 gachas) record every limited ace of the game (10–30 units), the
   banners show four to six (e.g. SO3: Blossom/Bride/Seaside Maria, Summer/メイドのソフィア).
5. (2018年福袋: applied, under 1.)
6. **Reviewed, kept: banners whose panels carry no content id** (R-PU-IMAGE uses only the rows with
   one): EP2公開記念ピックアップキャラガチャ (2018-07-19) records Bride Eve only (row 6), but panels 2 and 3
   show plain Evelysse and Verda (panels 1, 4, 5 and 6 are lost; 6 is the one the master names).
7. **Probably showcases, no change (d):** the 2017 ステップアップキャラガチャ / 氷属性ピックアップ step-ups
   (list banners only; "★5確率2倍/3倍" over a showcase; 氷属性 says "★5氷属性キャラ1体確定" over Ashton,
   Mavelle, Official Reimi — a BANNER_ART candidate if that reading is accepted), 300万DL記念,
   キャスターピックアップ確定 (Myuria; a class pick-up that R-PU-ROLEPICK doesn't match, the title lacks
   "ロールピックアップ"), 新生活応援無料ガチャ (nine units already in its S pool).
8. **発売日記念 (SO2–SO5) extras** are base or official costumes of the cast not matched on crowded
   group art; probable detector misses, no change.

**The event demos' gachas (checked 2026-10-06).** 復刻水着2020(1) (`gacha_pickup_role_1211`–`1220`, the
summer demo's banner) is *confirmed*: its panel `20200730_chara_PU_003` shows 常夏のベルダ and 常夏のクレア,
the recorded pick-ups. The NieR rerun (`gacha_pickup_role_0283`, the NieR demo) is *banner not
available*: its banner and panels are lost and the tool doesn't read the stand-ins; its pick-ups
(R-PU-IMAGE: the master's panels `pickup_img_chara_0015..0017` name 2B, 9S and A2) are what the stand-in
panels show. Neither gacha's pick-ups or pools changed in the update above (only the pool set ids were
renumbered). Drawn through soa-server (a replay of 55 10-draws of 0283 and six rounds of the 1211 step-up
chain, `--enable-events --seed-rng 1`): every S draw was a pick-up (0283: 11 2B, 9 9S, 16 A2 of 550
draws; 1211–1220: 17 Verda, 27 Clair of 600), and in the client the demos draw A2 and 9S (NieR) and
the banner shows the two summer units (screens in `work/test/{nier,summer}-demonstration`).

After the fixes the remaining *extra* rows are findings 3, 4, 8, EP2 CHAPTER:10 (アンリ, see 1) and
2018年福袋 (the banner shows three of its eleven, plus the later brides kept).

## Results

Confirmed gachas by pick-up source: R-PU-IMAGE 350, R-PU-THEME 240, R-PU-SIBLING 180,
R-PU-BANNERART 116, R-PU-RERUN 30, R-PU-NAME 16, R-PU-GROUP 3, R-PU-NEW 1 (677 of the 936 with the
main panel present). The R-PU-IMAGE ones are partly circular (the named panel is the rule's own
source). The R-PU-THEME, -SIBLING, -RERUN and -NAME confirmations are independent evidence for those
(c)/(d) rules. The R-PU-BANNERART ones are by construction.

<!-- BEGIN GENERATED (tools/gacha_verify.py) -->
| status | gachas | role | box | weapon | banner groups |
|---|---:|---:|---:|---:|---:|
| confirmed | 936 | 936 | 0 | 0 | 154 |
| missing from pickup | 14 | 14 | 0 | 0 | 12 |
| extra in pickup | 38 | 38 | 0 | 0 | 16 |
| mismatch (both) | 0 | 0 | 0 | 0 | 0 |
| inconclusive | 52 | 52 | 0 | 0 | 23 |
| banner not available | 607 | 342 | 265 | 0 | 143 |
| permanent showcase | 7 | 7 | 0 | 0 | 7 |
| box (detections listed) | 169 | 0 | 169 | 0 | 24 |
| weapon (not checked) | 458 | 0 | 0 | 458 | 99 |
| **total** | 2281 | | | | |

**Measured accuracy** (detections accepted at the threshold in bold; tp = a labelled character found, fn = missed, other = a character found that the label doesn't name):

| ground truth | images | >= 6 | >= 8 | >= 10 | >= 12 | >= 15 | >= 20 |
|---|---:|---|---|---|---|---|---|
| named panel | 82 | 82/82 +0 | 82/82 +0 | **82/82 +0** | 82/82 +0 | 82/82 +0 | 82/82 +0 |
| list banner | 78 | 156/178 +0 | **150/178 +0** | 140/178 +0 | 127/178 +0 | 111/178 +0 | 90/178 +0 |
| main panel | 34 | 63/65 +2 | 63/65 +2 | **63/65 +2** | 63/65 +2 | 63/65 +2 | 62/65 +2 |

Cells are recall `tp/(tp+fn)` and `+other`. Negative control: 173 weapon banners, 0 raw detections (>= 6 inliers), 0 accepted.
- main panel, missed: `pickup_img_chara_1704_002`: Bride Eve `cp0002_b03a`; `pickup_img_chara_1709_003`: Bride Eve `cp0002_b03a`
- main panel, other: `pickup_img_chara_1704_002`: Evelysse `cp0002_b01a`; `pickup_img_chara_1709_003`: Verda `cp0005_b01a`
- list banner, missed: `20200101_chara_002`: ヨシュア `cp0109_b01a`, エリス `cp0113_b01a`; `20200430_chara_002`: エリス `cp0113_b01a`, ボーマン `cp0206_b01a`, Chisato (蒼星のチサト) `cp0212_b02a`; `20200430_chara_003`: 蒼星のクロード `cp0201_b03a`, 蒼星のレナ `cp0202_b06a`, ノエル `cp0211_b01a`, スフレ `cp0308_b01a`, バッカス `cp0405_b01a`; `20200625_chara_002`: ヒーローベルダ `cp0005_b03a`; `20200625_chara_003`: Winter Evelysse `cp0002_b04a`, 渚のイヴリーシュ `cp0002_b05a`, Sweet Verda `cp0005_b02a`, 渚のラティクス `cp0101_b02a`, Cat Rena `cp0202_b03a`, 雪花レナ `cp0202_b05a`, Holiday Precis `cp0205_b02a`, Blossom Dias `cp0207_b02a`, Blossom Maria `cp0303_b03a`, Maid Nel `cp0305_b03a`, Maid Clair `cp0312_b03a`, 聖夜クレア `cp0312_b05a`, Winter Fidel `cp0501_b02a`, かぼちゃリリア `cp0507_b02a`, Dream Welch `cp0508_b03a`; `20200806_chara_001`: 水着カーリン `cp0015_b03a`, 水着ネル `cp0305_b05a`

### Mismatches

One row per banner (gachas with the same images and outcome: the steps of a step-up, single / 10-draw variants, reruns under one banner). *Detected, not recorded* lists each character with the rank of this gacha's pools that holds it (S, A, B, C, or - for none). Sheets: `work/gacha-verify/sheets/<first id>.png`; images `png/<name>.png` beside them.

| status | opened | gachas | title | source | images | detected, not recorded | recorded, not seen | sheet |
|---|---|---|---|---|---|---|---|---|
| missing from pickup | 2016-12-28 | gacha_fes_role_0003 | ３００万ＤＬ記念キャラガチャ（１人１回） | none | `pickup_img_chara_001`, `pickup_img_chara_002` | Fidel `cp0501_b01a` (S), Myuria `cp0408_b01a` (S) | - | `gacha_fes_role_0003.png` |
| missing from pickup | 2017-07-01 | gacha_pickup_role_0051 +2 | キャスターピックアップ確定ガチャ（毎日１回） | none | `pickup_img_chara_002` | Myuria `cp0408_b01a` (S) | - | `gacha_pickup_role_0051.png` |
| missing from pickup | 2017-11-09 | gacha_pickup_role_step_0002 | ステップアップキャラガチャ２(10連★5確率1枠10%) | none | `banner_gacha_pickup_role_0082` | Ilia `cp0105_b01a` (A), Lymle `cp0404_b01a` (A), Fayt `cp0301_b01a` (S), Ashton `cp0204_b01a` (S) | - | `gacha_pickup_role_step_0002.png` |
| missing from pickup | 2017-11-09 | gacha_pickup_role_step_0003 | ステップアップキャラガチャ３(10連★5確率1枠15%） | none | `banner_gacha_pickup_role_0083` | Ilia `cp0105_b01a` (A), Lymle `cp0404_b01a` (A), Fayt `cp0301_b01a` (S), Ashton `cp0204_b01a` (S) | - | `gacha_pickup_role_step_0003.png` |
| missing from pickup | 2017-12-04 | gacha_pickup_role_step_0007 | ステップアップキャラガチャ１(半額10連2500紋章石） | none | `banner_gacha_pickup_role_0092` | Verda `cp0005_b01a` (S), Official Edge `cp0401_b02a` (S), Faize `cp0403_b01a` (A) | - | `gacha_pickup_role_step_0007.png` |
| missing from pickup | 2017-12-04 | gacha_pickup_role_step_0008 | ステップアップキャラガチャ２(10連★5確率1枠10%) | none | `banner_gacha_pickup_role_0093` | Verda `cp0005_b01a` (S), Official Edge `cp0401_b02a` (S), Faize `cp0403_b01a` (A) | - | `gacha_pickup_role_step_0008.png` |
| missing from pickup | 2017-12-04 | gacha_pickup_role_step_0009 | ステップアップキャラガチャ３(10連★5確率1枠15%） | none | `banner_gacha_pickup_role_0094` | Verda `cp0005_b01a` (S), Official Edge `cp0401_b02a` (S), Faize `cp0403_b01a` (A) | - | `gacha_pickup_role_step_0009.png` |
| missing from pickup | 2017-12-18 | gacha_pickup_role_step_0010 | 氷属性ピックアップキャラガチャ１ | none | `banner_gacha_pickup_role_0111` | Ashton `cp0204_b01a` (S), Mavelle `cp0110_b01a` (S), Official Reimi `cp0402_b03a` (S) | - | `gacha_pickup_role_step_0010.png` |
| missing from pickup | 2017-12-18 | gacha_pickup_role_step_0011 | 氷属性ピックアップキャラガチャ２ | none | `banner_gacha_pickup_role_0112` | Ashton `cp0204_b01a` (S), Mavelle `cp0110_b01a` (S), Official Reimi `cp0402_b03a` (S) | - | `gacha_pickup_role_step_0011.png` |
| missing from pickup | 2017-12-18 | gacha_pickup_role_step_0012 | 氷属性ピックアップキャラガチャ３ | none | `banner_gacha_pickup_role_0113` | Mavelle `cp0110_b01a` (S), Official Reimi `cp0402_b03a` (S), Ashton `cp0204_b01a` (S) | - | `gacha_pickup_role_step_0012.png` |
| extra in pickup | 2018-01-01 | gacha_pickup_role_0109 | 2018年福袋限定チケットガチャ(花嫁/水着/ハロウィンのみ) | R-PU-BANNERART,R-PU-NAME | `banner_gacha_pickup_role_0118`, `pickup_img_chara_1712_017` | - | Bride Eve `cp0002_b03a`, 刻星のティカ (花嫁ティカ) `cp0011_b04a`, カーリン (花嫁カーリン) `cp0015_b06a`, Were-Millie `cp0102_b02a`, 花嫁プリシス `cp0205_b03a`, Summer Sophia `cp0302_b02a`, Bride Maria `cp0303_b02a`, Bride Nel `cp0305_b02a`, 花嫁ミラージュ `cp0310_b03a`, 花嫁クレア `cp0312_b04a`, 花嫁レイミ `cp0402_b04a`, Summer Myuria `cp0408_b02a`, Summer Miki `cp0502_b03a`, Vampire Victor `cp0503_b02a` | `gacha_pickup_role_0109.png` |
| missing from pickup | 2018-07-19 | gacha_pickup_role_0145 | EP2公開記念ピックアップキャラガチャ | R-PU-IMAGE | `pickup_img_chara_1704_002`, `pickup_img_chara_1709_003` | Verda `cp0005_b01a` (A), Evelysse `cp0002_b01a` (A) | Bride Eve `cp0002_b03a` (images incomplete: not judged) | `gacha_pickup_role_0145.png` |
| extra in pickup | 2019-05-01 | gacha_pickup_role_0202 | EP2 CHAPTER：10 公開記念キャラガチャ | R-PU-BANNERART,R-PU-IMAGE | `20190501_chara_PU_002`, `20190501_chara_PU_001` | - | アンリ `cp0017_b01a` | `gacha_pickup_role_0202.png` |
| extra in pickup | 2019-12-19 | gacha_pickup_role_0253 | SO3メモリアルピックアップキャラガチャ | R-PU-SERIES | `20191219_chara_002`, `20191219_chara_PU_001` | - | 花婿フェイト `cp0301_b02a`, ＳＲＦフェイト `cp0301_b03a`, ＳＲＦソフィア `cp0302_b05a`, 歌星ソフィア `cp0302_b06a`, 兎耳のマリア `cp0303_b05a`, Maria (銀雪マリア) `cp0303_b06a`, 花婿クリフ `cp0304_b02a`, Bride Nel `cp0305_b02a`, Maid Nel `cp0305_b03a`, 堕天使ネル `cp0305_b04a`, 水着ネル `cp0305_b05a`, 狼アルベル `cp0306_b03a`, 兎耳のミラージュ `cp0310_b02a`, 花嫁ミラージュ `cp0310_b03a`, Devil Clair `cp0312_b02a`, Maid Clair `cp0312_b03a`, 花嫁クレア `cp0312_b04a`, 聖夜クレア `cp0312_b05a` | `gacha_pickup_role_0253.png` |
| extra in pickup | 2020-02-19 | gacha_pickup_role_0279 +1 | SO4発売日記念ガチャ | R-PU-SERIES | `20200213_chara_003`, `20200213_chara_PU_003` | - | Official Edge `cp0401_b02a`, Official Reimi `cp0402_b03a`, Faize `cp0403_b01a`, Official Lymle `cp0404_b01b`, Youth Meracle `cp0406_b02a` | `gacha_pickup_role_0279.png` |
| extra in pickup | 2020-02-27 | gacha_pickup_role_0281 +1 | SO3発売日記念ガチャ | R-PU-SERIES | `20200227_chara_003`, `20200227_chara_PU_003` | - | Youth Sophia `cp0302_b03a`, Cliff `cp0304_b01a`, Dark Albel `cp0306_b02a`, Clair `cp0312_b01a` | `gacha_pickup_role_0281.png` |
| extra in pickup | 2020-03-05 | gacha_pickup_role_0255 | SO2メモリアルピックアップキャラガチャ | R-PU-SERIES | `20191226_chara_003`, `20191226_chara_PU_001` | - | 雪花レナ `cp0202_b05a`, Rena (鏡宮のレナ) `cp0202_b07a`, Rena (泉郷レナ) `cp0202_b08a`, Celine (ハンターセリーヌ) `cp0203_b02a`, 雪空アシュトン `cp0204_b03a`, Holiday Precis `cp0205_b02a`, Precis (魔改のプリシス) `cp0205_b05a`, Blossom Dias `cp0207_b02a`, 執事のレオン `cp0208_b02a` | `gacha_pickup_role_0255.png` |
| missing from pickup | 2020-03-12 | gacha_pickup_role_0303 | 新生活応援無料ガチャ | none | `20200312_chara_006`, `20200312_chara_PU_005` | ウェルチ `cp0014_b01a` (S), 灼炎のアシュトン `cp0204_b02a` (S), ペリシー `cp0112_b01a` (S), Crimson Phia `cp0108_b02a` (S), ユーイン `cp0013_b01a` (S), Youth Meracle `cp0406_b02a` (S), Dark Albel `cp0306_b02a` (S), Lucifer `cm413_b01a` (S), Cyuss `cp0106_b01a` (S) | - | `gacha_pickup_role_0303.png` |
| extra in pickup | 2020-03-31 | gacha_pickup_role_0302 +1 | SO5発売日記念ガチャ | R-PU-SERIES | `20200326_chara_005`, `20200326_chara_PU_005` | - | Official Anne `cp0506_b02a`, Daril `cp0509_b01a` | `gacha_pickup_role_0302.png` |
| extra in pickup | 2020-05-07 | gacha_pickup_role_0335 +1 | SO5メモリアルピックアップキャラガチャ | R-PU-SERIES | `20200507_chara_001`, `20200507_chara_PU_001` | - | Winter Fidel `cp0501_b02a`, Miki (甘恋のミキ) `cp0502_b05a`, Vampire Victor `cp0503_b02a`, かぼちゃリリア `cp0507_b02a`, Dream Welch `cp0508_b03a` | `gacha_pickup_role_0335.png` |
| extra in pickup | 2020-06-01 | gacha_pickup_role_0351 | SO1メモリアルピックアップキャラガチャ | R-PU-SERIES | `20200528_chara_002`, `20200528_chara_PU_003` | - | 渚のラティクス `cp0101_b02a`, エリス (天翼のエリス) `cp0113_b02a` | `gacha_pickup_role_0351.png` |
| extra in pickup | 2020-07-30 | gacha_pickup_role_0425 | SO2発売日記念ガチャ | R-PU-SERIES | `20200730_chara_005`, `20200730_chara_PU_004` | - | 蒼星のクロード `cp0201_b03a`, 蒼星のレナ `cp0202_b06a`, Celine `cp0203_b01a`, Ashton `cp0204_b01a`, 灼炎のアシュトン `cp0204_b02a`, Dias `cp0207_b01a`, Leon (蒼星のレオン) `cp0208_b03a`, Opera `cp0209_b01a`, 紅輝のオペラ `cp0209_b02a`, Chisato `cp0212_b01a`, Chisato (蒼星のチサト) `cp0212_b02a` | `gacha_pickup_role_0425.png` |
| extra in pickup | 2020-09-03 | gacha_pickup_role_0470 | SO3メモリアルピックアップキャラガチャ | R-PU-SERIES | `20200903_chara_001`, `20200903_chara_PU_001` | - | Fayt (神翼のフェイト) `cp0301_b04a`, Summer Sophia `cp0302_b02a`, メイドのソフィア `cp0302_b04a`, ＳＲＦソフィア `cp0302_b05a`, 歌星ソフィア `cp0302_b06a`, Bride Maria `cp0303_b02a`, Blossom Maria `cp0303_b03a`, Seaside Maria `cp0303_b04a`, 兎耳のマリア `cp0303_b05a`, Maria (銀雪マリア) `cp0303_b06a`, Maria (神翼のマリア) `cp0303_b07a`, 花婿クリフ `cp0304_b02a`, Bride Nel `cp0305_b02a`, Maid Nel `cp0305_b03a`, 堕天使ネル `cp0305_b04a`, 水着ネル `cp0305_b05a`, Nel (華王妃ネル) `cp0305_b06a`, Nel (斬鬼のネル) `cp0305_b07a`, 狼アルベル `cp0306_b03a`, Albel (鬼炎のアルベル) `cp0306_b04a`, 花嫁ミラージュ `cp0310_b03a`, Devil Clair `cp0312_b02a`, Maid Clair `cp0312_b03a`, 花嫁クレア `cp0312_b04a`, 聖夜クレア `cp0312_b05a`, Clair (華王妃クレア) `cp0312_b06a`, Clair (常夏のクレア) `cp0312_b07a` | `gacha_pickup_role_0470.png` |
| extra in pickup | 2020-11-05 | gacha_pickup_role_0565 | SO3メモリアルピックアップキャラガチャ | R-PU-SERIES | `20191219_chara_002`, `20191219_chara_PU_001` | - | 花婿フェイト `cp0301_b02a`, ＳＲＦフェイト `cp0301_b03a`, Fayt (神翼のフェイト) `cp0301_b04a`, ＳＲＦソフィア `cp0302_b05a`, 歌星ソフィア `cp0302_b06a`, 兎耳のマリア `cp0303_b05a`, Maria (銀雪マリア) `cp0303_b06a`, Maria (神翼のマリア) `cp0303_b07a`, Maria (吸血鬼マリア) `cp0303_b08a`, 花婿クリフ `cp0304_b02a`, Bride Nel `cp0305_b02a`, Maid Nel `cp0305_b03a`, 堕天使ネル `cp0305_b04a`, 水着ネル `cp0305_b05a`, Nel (華王妃ネル) `cp0305_b06a`, Nel (斬鬼のネル) `cp0305_b07a`, 狼アルベル `cp0306_b03a`, Albel (鬼炎のアルベル) `cp0306_b04a`, スフレ (奇術師スフレ) `cp0308_b02a`, 兎耳のミラージュ `cp0310_b02a`, 花嫁ミラージュ `cp0310_b03a`, Devil Clair `cp0312_b02a`, Maid Clair `cp0312_b03a`, 花嫁クレア `cp0312_b04a`, 聖夜クレア `cp0312_b05a`, Clair (華王妃クレア) `cp0312_b06a`, Clair (常夏のクレア) `cp0312_b07a` | `gacha_pickup_role_0565.png` |
| extra in pickup | 2020-11-19 | gacha_pickup_role_0590 | SO2メモリアルピックアップキャラガチャ | R-PU-SERIES | `20191226_chara_003`, `20191226_chara_PU_001` | - | 雪花レナ `cp0202_b05a`, Rena (鏡宮のレナ) `cp0202_b07a`, Rena (泉郷レナ) `cp0202_b08a`, Rena (神星のレナ) `cp0202_b09a`, Celine (ハンターセリーヌ) `cp0203_b02a`, 雪空アシュトン `cp0204_b03a`, Ashton (神龍のアシュトン) `cp0204_b04a`, Holiday Precis `cp0205_b02a`, Precis (魔改のプリシス) `cp0205_b05a`, Blossom Dias `cp0207_b02a`, 執事のレオン `cp0208_b02a` | `gacha_pickup_role_0590.png` |
| extra in pickup | 2021-05-06 | gacha_pickup_role_0900 | SO2メモリアルピックアップキャラガチャ | R-PU-SERIES | `20191226_chara_003`, `20191226_chara_PU_001` | - | 雪花レナ `cp0202_b05a`, Rena (鏡宮のレナ) `cp0202_b07a`, Rena (泉郷レナ) `cp0202_b08a`, Rena (神星のレナ) `cp0202_b09a`, Rena (歌星レナ) `cp0202_b10a`, Celine (ハンターセリーヌ) `cp0203_b02a`, 雪空アシュトン `cp0204_b03a`, Ashton (神龍のアシュトン) `cp0204_b04a`, Holiday Precis `cp0205_b02a`, Precis (魔改のプリシス) `cp0205_b05a`, Precis (甘砲のプリシス) `cp0205_b06a`, Blossom Dias `cp0207_b02a`, 執事のレオン `cp0208_b02a` | `gacha_pickup_role_0900.png` |
| extra in pickup | 2021-05-06 | gacha_pickup_role_0951 +9 | 復刻水着2018(1)/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | `20210506_chara_003`, `20210506_chara_PU_003` | - | 渚のイヴリーシュ `cp0002_b05a`, 渚のラティクス `cp0101_b02a`, 渚のレナ `cp0202_b04a` | `gacha_pickup_role_0951.png` |
| extra in pickup | 2021-05-06 | gacha_pickup_role_0961 +9 | 復刻水着2018(2)/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | `20210506_chara_004`, `20210506_chara_PU_004` | - | Seaside Millie `cp0102_b03a`, Seaside Maria `cp0303_b04a` | `gacha_pickup_role_0961.png` |

### Inconclusive

No character detected, or recorded pick-ups not seen where only the list banner or some of the per-character panels survive.

| opened | gachas | title | source | images | detected | recorded, not seen |
|---|---|---|---|---|---|---|
| 2017-04-06 | gacha_pickup_role_0013 | ピックアップガチャ(イヴリーシュ/ミカエル) | R-PU-NAME | `pickup_img_chara_1704_002` | Evelysse `cp0002_b01a` | Michael `cm409_b01a` |
| 2017-04-15 | gacha_pickup_role_0015 | ピックアップガチャ(ネル/クレア) | R-PU-NAME | `pickup_img_chara_004` | Nel `cp0305_b01a` | Clair `cp0312_b01a` |
| 2017-04-19 | gacha_pickup_role_0017 | ピックアップガチャ(ミュリア/アンヌ) | R-PU-NAME | `pickup_img_chara_002` | Myuria `cp0408_b01a` | Anne `cp0506_b01a` |
| 2017-09-14 | gacha_pickup_role_0065 | ピックアップガチャ(プリシス/ベルダ) | R-PU-NAME | `pickup_img_chara_1709_003` | Verda `cp0005_b01a` | Precis `cp0205_b01a` |
| 2017-10-26 | gacha_pickup_role_0081 | ピックアップ(悪魔クレア/吸血鬼ヴィクトル/狼ミリー） | R-PU-NAME | `pickup_img_chara_1710_016` | Devil Clair `cp0312_b02a` | Were-Millie `cp0102_b02a`, Vampire Victor `cp0503_b02a` |
| 2017-11-01 | gacha_pickup_role_0083 | SO5キャラピックアップガチャ（期間中3回） | R-PU-SERIES | `pickup_img_chara_001`, `pickup_img_chara_008` | Fidel `cp0501_b01a`, Miki `cp0502_b01a` | Victor `cp0503_b01a`, Fiore `cp0504_b01a`, Emmerson `cp0505_b01a`, Anne `cp0506_b01a`, Official Anne `cp0506_b02a`, Relia `cp0507_b01a`, Daril `cp0509_b01a` |
| 2018-05-17 | gacha_pickup_role_0127 | ピックアップキャラガチャ(青春のメリクル/ルシフェル) | R-PU-IMAGE | `pickup_img_chara_0045` | Youth Meracle `cp0406_b02a` | Lucifer `cm413_b01a` |
| 2018-08-23 | gacha_pickup_role_0150 | メモリアル★5キャラピックアップ | R-PU-IMAGE | `pickup_img_chara_1710_016` | Devil Clair `cp0312_b02a` | Blossom Maria `cp0303_b03a`, Winter Fidel `cp0501_b02a`, Dream Welch `cp0508_b03a` |
| 2018-08-30 | gacha_pickup_role_0151 | ピックアップキャラガチャ（メイドのソフィア/執事のレオン） | R-PU-IMAGE | `pickup_img_chara_0090` | 執事のレオン `cp0208_b02a` | メイドのソフィア `cp0302_b04a` |
| 2019-02-01 | gacha_pickup_role_0186 | ピックアップキャラガチャ(甘狐のカーリン/天真のペリシー) | R-PU-IMAGE | `20190131_chara_PU_002` | 天真のペリシー `cp0112_b02a` | 甘狐のカーリン `cp0015_b02a` |
| 2019-02-14 | gacha_pickup_role_0189 | ピックアップキャラガチャ(ヴァルカ/アンリ/バッカス) | R-PU-IMAGE | `20190214_chara_PU_002`, `20190214_chara_PU_003` | バッカス `cp0405_b01a`, アンリ `cp0017_b01a` | ヴァルカ `cp0016_b01a` |
| 2019-07-01 | gacha_pickup_role_0210 +10 | ｳｪﾃﾞｨﾝｸﾞｽﾍﾟｼｬﾙｷｬﾗｶﾞﾁｬ(花嫁ミラージュ/花婿クリフ) | R-PU-IMAGE | `20190627_chara_PU_002` | 花嫁ミラージュ `cp0310_b03a` | 花婿クリフ `cp0304_b02a` |
| 2019-07-27 | gacha_pickup_role_0217 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | `20190131_chara_PU_002`, `20190207_chara_PU_001` | 天真のペリシー `cp0112_b02a`, 凛花リムル `cp0404_b02a` | 迎春イヴリーシュ `cp0002_b06a`, 迎春ティカ `cp0010_b02a`, 甘狐のカーリン `cp0015_b02a` |
| 2019-08-29 | gacha_pickup_role_0225 | ピックアップキャラガチャ(花魁ミュリア/ハンターセリーヌ) | R-PU-IMAGE | `20190829_chara_PU_002` | Celine (ハンターセリーヌ) `cp0203_b02a` | Myuria (花魁ミュリア) `cp0408_b03a` |
| 2019-09-26 | gacha_pickup_role_0230 | 【復刻】ピックアップキャラガチャ　メイド | R-PU-IMAGE | `pickup_img_chara_0090` | 執事のレオン `cp0208_b02a` | メイドのソフィア `cp0302_b04a`, Maid Nel `cp0305_b03a`, Maid Clair `cp0312_b03a` |
| 2020-06-25 | gacha_pickup_role_starpickup_001 | 3倍!スターピックアップキャラガチャ | R-PU-IMAGE | `20200625_chara_003` | - | 渚のイヴリーシュ `cp0002_b05a`, Holiday Precis `cp0205_b02a`, かぼちゃリリア `cp0507_b02a` |
| 2020-07-02 | gacha_pickup_role_starpickup_002 | 3倍!スターピックアップキャラガチャ | R-PU-IMAGE | `20200625_chara_003` | - | 渚のラティクス `cp0101_b02a`, 雪花レナ `cp0202_b05a`, Blossom Maria `cp0303_b03a` |
| 2020-07-09 | gacha_pickup_role_starpickup_003 | 3倍!スターピックアップキャラガチャ | R-PU-IMAGE | `20200625_chara_003` | - | Cat Rena `cp0202_b03a`, Blossom Dias `cp0207_b02a`, Maid Nel `cp0305_b03a` |
| 2020-07-16 | gacha_pickup_role_202007_owabi | お詫びキャラガチャ　2020年7月 | none | `20200716_chara_002`, `20200716_chara_PU_002` | - | - |
| 2020-07-16 | gacha_pickup_role_starpickup_004 | 3倍!スターピックアップキャラガチャ | R-PU-IMAGE | `20200625_chara_003` | - | Winter Evelysse `cp0002_b04a`, Sweet Verda `cp0005_b02a`, 聖夜クレア `cp0312_b05a` |
| 2020-07-22 | gacha_pickup_role_0411 | SO４メモリアルピックアップキャラガチャ | R-PU-IMAGE | `20190207_chara_PU_001` | 凛花リムル `cp0404_b02a` | Faize (祓魔師フェイズ) `cp0403_b02a`, Myuria (花魁ミュリア) `cp0408_b03a` |
| 2020-07-22 | gacha_pickup_role_starpickup_005 | 3倍!スターピックアップキャラガチャ | R-PU-IMAGE | `20200625_chara_003` | - | Maid Clair `cp0312_b03a`, Winter Fidel `cp0501_b02a`, Dream Welch `cp0508_b03a` |
| 2020-08-06 | gacha_pickup_role_0436 +19 | 10連10ステップ目PU1体確定水着2019 ステップ1 | R-PU-IMAGE | `20200806_chara_001` | 水着エッジ `cp0401_b03a`, 水着大人ティカ `cp0011_b02a` | 水着カーリン `cp0015_b03a`, 水着ネル `cp0305_b05a` |

### Box gachas: characters on their banners

<details><summary>show</summary>

| opened | gachas | title | detected |
|---|---|---|---|

</details>

### Permanent banners: showcased characters

<details><summary>show</summary>

| opened | gachas | title | detected |
|---|---|---|---|
| 2016-01-01 | gacha_role_0001 | キャラガチャ | カーリン `cp0015_b01a` (S), Ronyx `cp0104_b01a` (A), Fayt `cp0301_b01a` (S), Evelysse `cp0002_b01a` (S), バッカス `cp0405_b01a` (S), 蒼星のクロード `cp0201_b03a` (S) |
| 2016-01-01 | ticketgacha_role_0001 | ★４キャラガチャチケット | Shimada `cp0413_b01a` (B), Pavine `cp0510_b01a` (B), Farleen `cp0314_b01a` (B), Welch `cp0508_b01a` (B) |
| 2016-01-01 | ticketgacha_role_0002 | ★４～５キャラガチャチケット | Verda `cp0005_b01a` (S), Faize `cp0403_b01a` (A), Edge `cp0401_b01a` (S), Raffine `cp0518_b01a` (B), Phia `cp0108_b01a` (A), ヴァルカ `cp0016_b01a` (S), Tynave `cp0313_b01a` (B) |
| 2016-01-01 | ticketgacha_role_0003 | ★５キャラガチャチケット | Fidel `cp0501_b01a` (S), Relia `cp0507_b01a` (S), Youth Meracle `cp0406_b02a` (S), エイルマット `cp0409_b01a` (S), Lymle `cp0404_b01a` (A), Dark Albel `cp0306_b02a` (S), Verda `cp0005_b01a` (S) |
| 2016-01-01 | ticketgacha_role_0004 | ★５エースキャラガチャチケット | 灼炎のアシュトン `cp0204_b02a` (S), ユーイン `cp0013_b01a` (S), 紅輝のオペラ `cp0209_b02a` (S), Youth Sophia `cp0302_b03a` (S), ペリシー `cp0112_b01a` (S) |
| 2020-02-20 | gacha_galaxy_role | ギャラクシーキャラガチャ | Leon `cp0208_b01a` (S), スフレ `cp0308_b01a` (S), Official Anne `cp0506_b02a` (S), ウェルチ `cp0014_b01a` (S), Chisato (蒼星のチサト) `cp0212_b02a` (S), エイルマット `cp0409_b01a` (S), アンリ `cp0017_b01a` (S), Ashton `cp0204_b01a` (S) |
| 2020-06-25 | gacha_sphere211_role_001 | スフィア211キャラガチャ | バッカス `cp0405_b01a` (S), ヨシュア `cp0109_b01a` (S), マスティマ `cp0019_b01a` (S), アンリ `cp0017_b01a` (S), Chisato (蒼星のチサト) `cp0212_b02a` (S), スフレ `cp0308_b01a` (S) |

</details>

### Confirmed

<details><summary>show</summary>

| opened | gachas | title | source | pick-ups (all seen) |
|---|---|---|---|---|
| 2017-04-13 | gacha_pickup_role_0014 | ピックアップガチャ(マリア/クリフ) | R-PU-NAME | Maria `cp0303_b01a`, Cliff `cp0304_b01a` |
| 2017-04-23 | gacha_pickup_role_0019 | ピックアップガチャ(フィデル/ミキ/ヴィクトル) | R-PU-NAME | Fidel `cp0501_b01a`, Miki `cp0502_b01a`, Victor `cp0503_b01a` |
| 2017-09-28 | gacha_pickup_role_0066 | ラスウェル確定ガチャ | R-PU-NAME | Lasswell `cc0006_b01a` |
| 2017-11-20 | gacha_pickup_role_0086 | ピックアップガチャ(シグムント） | R-PU-NAME | シグムント `cc0009_b01a` |
| 2017-11-20 | gacha_pickup_role_step_0004 | ステップアップシグムントガチャ１(10連2500紋章石） | R-PU-BANNERART | シグムント `cc0009_b01a` |
| 2017-11-20 | gacha_pickup_role_step_0005 | ステップアップシグムントガチャ２(10連のみ1枠2%） | R-PU-BANNERART | シグムント `cc0009_b01a` |
| 2017-11-20 | gacha_pickup_role_step_0006 | ステップアップシグムントガチャ３(10連のみ1枠3%） | R-PU-BANNERART | シグムント `cc0009_b01a` |
| 2017-12-07 | gacha_pickup_role_0090 | ラティクス確定ガチャ | R-PU-NAME | Roddick `cp0101_b01a` |
| 2017-12-07 | gacha_pickup_role_0091 | マーヴェル確定ガチャ | R-PU-NAME | Mavelle `cp0110_b01a` |
| 2017-12-07 | gacha_pickup_role_0092 | アシュトン確定ガチャ | R-PU-NAME | Ashton `cp0204_b01a` |
| 2017-12-07 | gacha_pickup_role_0093 | プリシス確定ガチャ | R-PU-NAME | Precis `cp0205_b01a` |
| 2017-12-07 | gacha_pickup_role_0094 | ミラージュ確定ガチャ | R-PU-NAME | Mirage `cp0310_b01a` |
| 2017-12-07 | gacha_pickup_role_0095 | アルベル確定ガチャ | R-PU-NAME | Albel `cp0306_b01a` |
| 2017-12-07 | gacha_pickup_role_0096 | クロウ確定ガチャ | R-PU-NAME | Crowe `cp0411_b01a` |
| 2017-12-07 | gacha_pickup_role_0097 | 連邦レイミ確定ガチャ | R-PU-NAME | Official Reimi `cp0402_b03a` |
| 2017-12-07 | gacha_pickup_role_0098 | フィオーレ確定ガチャ | R-PU-NAME | Fiore `cp0504_b01a` |
| 2017-12-07 | gacha_pickup_role_0099 | リリア確定ガチャ | R-PU-NAME | Relia `cp0507_b01a` |
| 2017-12-07 | gacha_pickup_role_0100 | イヴリーシュ確定ガチャ | R-PU-NAME | Evelysse `cp0002_b01a` |
| 2017-12-07 | gacha_pickup_role_0101 | ベルダ確定ガチャ | R-PU-NAME | Verda `cp0005_b01a` |
| 2017-12-14 | gacha_pickup_role_0104 | クリスマスキャラピックアップガチャ | R-PU-NEW | Winter Evelysse `cp0002_b04a`, Holiday Precis `cp0205_b02a`, Winter Fidel `cp0501_b02a` |
| 2018-07-12 | gacha_pickup_role_0137 | ピックアップキャラガチャ(灼炎のアシュトン/ペリシー) | R-PU-IMAGE | ペリシー `cp0112_b01a`, 灼炎のアシュトン `cp0204_b02a` |
| 2018-09-13 | gacha_pickup_role_0154 | ピックアップキャラガチャ（ユーイン/紅輝のオペラ） | R-PU-IMAGE | ユーイン `cp0013_b01a`, 紅輝のオペラ `cp0209_b02a` |
| 2018-09-27 | gacha_pickup_role_0157 +1 | ピックアップキャラガチャ(兎耳のマリア/兎耳のミラージュ) | R-PU-IMAGE | 兎耳のマリア `cp0303_b05a`, 兎耳のミラージュ `cp0310_b02a` |
| 2018-11-15 | gacha_pickup_role_0169 | ピックアップキャラガチャ（エイルマット/カーリン） | R-PU-IMAGE | カーリン `cp0015_b01a`, エイルマット `cp0409_b01a` |
| 2019-02-07 | gacha_pickup_role_0188 | ピックアップキャラガチャ(凛花リムル) | R-PU-IMAGE | 凛花リムル `cp0404_b02a` |
| 2019-03-14 | gacha_pickup_role_0193 +1 | ピックアップキャラガチャ(歌星ソフィア/歌星イヴリーシュ) | R-PU-IMAGE | 歌星イヴリーシュ `cp0002_b07a`, 歌星ソフィア `cp0302_b06a` |
| 2019-03-20 | gacha_pickup_role_0195 | ピックアップキャラガチャ(蒼星のレナ/蒼星のクロード) | R-PU-IMAGE | 蒼星のクロード `cp0201_b03a`, 蒼星のレナ `cp0202_b06a` |
| 2019-05-09 | gacha_pickup_role_0204 | ピックアップキャラガチャ(スフレ/ノエル) | R-PU-IMAGE | ノエル `cp0211_b01a`, スフレ `cp0308_b01a` |
| 2019-07-11 | gacha_pickup_role_0211 | ピックアップキャラガチャ(ボーマン) | R-PU-IMAGE | ボーマン `cp0206_b01a` |
| 2019-08-15 | gacha_pickup_role_0223 | ピックアップキャラガチャ(エリス/ヨシュア） | R-PU-IMAGE | ヨシュア `cp0109_b01a`, エリス `cp0113_b01a` |
| 2019-09-12 | gacha_pickup_role_0227 | ピックアップキャラガチャ(蒼星のチサト/蒼星のレオン） | R-PU-IMAGE | Leon (蒼星のレオン) `cp0208_b03a`, Chisato (蒼星のチサト) `cp0212_b02a` |
| 2019-12-12 | gacha_pickup_role_0252 | ピックアップキャラガチャ（銀雪マリア/雪猫ペリシー） | R-PU-IMAGE | ペリシー (雪猫ペリシー) `cp0112_b03a`, Maria (銀雪マリア) `cp0303_b06a` |
| 2020-01-01 | gacha_pickup_role_0258 | ピックアップキャラガチャ（鳳弓のレイミ/暁狐のカーリン） | R-PU-IMAGE | カーリン (暁狐のカーリン) `cp0015_b04a`, Reimi (鳳弓のレイミ) `cp0402_b06a` |
| 2020-01-01 | gacha_pickup_role_0260 | 新年お年玉ピックアップキャラガチャ | R-PU-IMAGE | 刻星のティカ `cp0011_b01a`, マスティマ `cp0019_b01a`, ヨシュア `cp0109_b01a`, エリス `cp0113_b01a`, スフレ `cp0308_b01a`, アドレー `cp0309_b01a` |
| 2020-01-02 | gacha_pickup_role_0259 | 復刻お正月ピックアップキャラガチャ | R-PU-IMAGE | 迎春イヴリーシュ `cp0002_b06a`, 迎春ティカ `cp0010_b02a` |
| 2020-01-23 | gacha_pickup_role_0273 | ピックアップキャラガチャ（華王妃ネル/華王妃クレア） | R-PU-IMAGE | Nel (華王妃ネル) `cp0305_b06a`, Clair (華王妃クレア) `cp0312_b06a` |
| 2020-01-23 | gacha_pickup_role_step_0263 +9 | 春節ガチャ 10連10ステップ目ＰＵ１体確定 ステップ1 | R-PU-IMAGE | Nel (華王妃ネル) `cp0305_b06a`, Clair (華王妃クレア) `cp0312_b06a` |
| 2020-02-13 | gacha_pickup_role_0277 | ピックアップキャラガチャ（天翼のエリス/甘恋のミキ） | R-PU-IMAGE | エリス (天翼のエリス) `cp0113_b02a`, Miki (甘恋のミキ) `cp0502_b05a` |
| 2020-02-13 | gacha_pickup_role_0278 | 復刻バレンタイン2019ピックアップキャラガチャ | R-PU-IMAGE | 甘狐のカーリン `cp0015_b02a`, 天真のペリシー `cp0112_b02a`, 凛花リムル `cp0404_b02a` |
| 2020-02-27 | gacha_pickup_role_0282 | ピックアップキャラガチャ（泉郷レナ/泉郷イヴリーシュ） | R-PU-IMAGE | Evelysse (泉郷イヴリーシュ) `cp0002_b09a`, Rena (泉郷レナ) `cp0202_b08a` |
| 2020-03-12 | gacha_pickup_role_0284 | ピックアップキャラガチャ（神翼のフェイト） | R-PU-IMAGE | Fayt (神翼のフェイト) `cp0301_b04a` |
| 2020-03-12 | gacha_pickup_role_0285 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1（神翼のフェイト） | R-PU-IMAGE | Fayt (神翼のフェイト) `cp0301_b04a` |
| 2020-03-12 | gacha_pickup_role_0295 | ホワイトデー限定復刻ピックアップキャラガチャ1 | R-PU-BANNERART | 渚のラティクス `cp0101_b02a`, Blossom Dias `cp0207_b02a`, 花婿フェイト `cp0301_b02a`, 水着エッジ `cp0401_b03a`, Winter Fidel `cp0501_b02a` |
| 2020-03-12 | gacha_pickup_role_0296 | ホワイトデー限定復刻ピックアップキャラガチャ2 | R-PU-BANNERART | 雪空アシュトン `cp0204_b03a`, 執事のレオン `cp0208_b02a`, 花婿クリフ `cp0304_b02a`, 狼アルベル `cp0306_b03a`, Vampire Victor `cp0503_b02a` |
| 2020-04-16 | gacha_pickup_role_0309 +29 | 10連10ステップ目PU1体確定アイドル2018 ステップ1 | R-PU-IMAGE | 歌星ベルダ `cp0005_b04a`, 歌星レイミ `cp0402_b05a`, 歌星ミキ `cp0502_b04a` |
| 2020-04-16 | gacha_pickup_role_0319 +29 | 10連10ステップ目PU1体確定アイドル2019 ステップ1 | R-PU-IMAGE | 歌星イヴリーシュ `cp0002_b07a`, 歌星ソフィア `cp0302_b06a` |
| 2020-04-30 | gacha_pickup_role_0332 | ピックアップキャラガチャ（狐将のカーリン/砲甲のリカルド） | R-PU-IMAGE | カーリン (狐将のカーリン) `cp0015_b05a`, リカルド (砲甲のリカルド) `cp0018_b03a` |
| 2020-04-30 | gacha_pickup_role_0333 | GWピックアップキャラガチャ 第一弾 | R-PU-IMAGE | ヨシュア `cp0109_b01a`, エリス `cp0113_b01a`, ボーマン `cp0206_b01a`, Leon (蒼星のレオン) `cp0208_b03a`, Chisato (蒼星のチサト) `cp0212_b02a`, アドレー `cp0309_b01a` |
| 2020-05-04 | gacha_pickup_role_0334 | GWピックアップキャラガチャ 第二弾 | R-PU-IMAGE | 蒼星のクロード `cp0201_b03a`, 蒼星のレナ `cp0202_b06a`, ノエル `cp0211_b01a`, スフレ `cp0308_b01a`, バッカス `cp0405_b01a`, エイルマット `cp0409_b01a` |
| 2020-05-14 | gacha_pickup_role_0336 | ピックアップキャラガチャ（神翼のマリア/賢神のマスティマ） | R-PU-IMAGE | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2020-05-14 | gacha_pickup_role_0337 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1\n（神翼のマリア/賢神のマスティマ） | R-PU-IMAGE | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2020-05-28 | gacha_pickup_role_0350 | ピックアップキャラガチャ(斬鬼のネル/鬼炎のアルベル) | R-PU-IMAGE | Nel (斬鬼のネル) `cp0305_b07a`, Albel (鬼炎のアルベル) `cp0306_b04a` |
| 2020-06-11 | gacha_pickup_role_0362 | ピックアップキャラガチャ（花嫁ティカ/花嫁カーリン） | R-PU-IMAGE | 刻星のティカ (花嫁ティカ) `cp0011_b04a`, カーリン (花嫁カーリン) `cp0015_b06a` |
| 2020-06-11 | gacha_pickup_role_0363 +19 | 10連10ステップ目PU1体確定花嫁2018 ステップ1 | R-PU-IMAGE | 花嫁プリシス `cp0205_b03a`, 花婿フェイト `cp0301_b02a`, 花嫁クレア `cp0312_b04a`, 花嫁レイミ `cp0402_b04a` |
| 2020-06-25 | gacha_pickup_role_0385 | ピックアップキャラガチャ（ヒース/ラヴァーニア） | R-PU-IMAGE | ヒース `cp0021_b01a`, ラヴァーニア `cp0022_b01a` |
| 2020-07-01 | gacha_pickup_role_0386 | SOAメモリアルピックアップキャラガチャ | R-PU-IMAGE | 歌星イヴリーシュ `cp0002_b07a`, ヒーローベルダ `cp0005_b03a`, 歌星ベルダ `cp0005_b04a`, 迎春ティカ `cp0010_b02a` |
| 2020-07-25 | gacha_pickup_role_0412 +1 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | ペリシー (雪猫ペリシー) `cp0112_b03a`, Maria (銀雪マリア) `cp0303_b06a` |
| 2020-07-30 | gacha_pickup_role_0413 | ロールピックアップキャラガチャ シューター | R-PU-IMAGE | 天真のペリシー `cp0112_b02a`, Celine (ハンターセリーヌ) `cp0203_b02a`, 執事のレオン `cp0208_b02a` |
| 2020-07-30 | gacha_pickup_role_0414 | ピックアップキャラガチャ(常夏のベルダ/常夏のクレア) | R-PU-IMAGE | Verda (常夏のベルダ) `cp0005_b06a`, Clair (常夏のクレア) `cp0312_b07a` |
| 2020-07-30 | gacha_pickup_role_0415 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1(常夏のベルダ/常夏のクレア) | R-PU-IMAGE | Verda (常夏のベルダ) `cp0005_b06a`, Clair (常夏のクレア) `cp0312_b07a` |
| 2020-08-06 | gacha_pickup_role_0426 +9 | 10連10ステップ目PU1体確定兎耳 ステップ1 | R-PU-IMAGE | 兎耳のマリア `cp0303_b05a`, 兎耳のミラージュ `cp0310_b02a` |
| 2020-08-13 | gacha_pickup_role_0446 | ピックアップキャラガチャ（真夏のウェルチ/真夏のユーイン） | R-PU-IMAGE | ユーイン (真夏のユーイン) `cp0013_b02a`, ウェルチ (真夏のウェルチ) `cp0014_b02a` |
| 2020-08-13 | gacha_pickup_role_0447 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1\n(真夏のウェルチ/真夏のユーイン) | R-PU-IMAGE | ユーイン (真夏のユーイン) `cp0013_b02a`, ウェルチ (真夏のウェルチ) `cp0014_b02a` |
| 2020-08-15 | gacha_pickup_role_0457 +1 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | カーリン (暁狐のカーリン) `cp0015_b04a`, Reimi (鳳弓のレイミ) `cp0402_b06a` |
| 2020-08-27 | gacha_pickup_role_0459 | ピックアップキャラガチャ（渚のエリス/渚のラヴァーニア） | R-PU-IMAGE | 渚のラヴァーニア `cp0022_b02a`, エリス (渚のエリス) `cp0113_b03a` |
| 2020-08-27 | gacha_pickup_role_0460 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1（渚のエリス/渚のラヴァーニア） | R-PU-IMAGE | 渚のラヴァーニア `cp0022_b02a`, エリス (渚のエリス) `cp0113_b03a` |
| 2020-09-03 | gacha_pickup_role_0471 +19 | 10連10ステップ目PU1体確定衣装コンテスト2019 ステップ1 | R-PU-BANNERART | Celine (ハンターセリーヌ) `cp0203_b02a`, Myuria (花魁ミュリア) `cp0408_b03a` |
| 2020-09-10 | gacha_pickup_role_0481 +1 | ピックアップキャラガチャ（神星のレナ） | R-PU-IMAGE | Rena (神星のレナ) `cp0202_b09a` |
| 2020-09-10 | gacha_pickup_role_0482 +9 | １０連１０ステップ目ＰＵ１体確定 ステップ1(神星のレナ) | R-PU-IMAGE | Rena (神星のレナ) `cp0202_b09a` |
| 2020-09-10 | gacha_pickup_role_0492 +2 | ピックアップキャラガチャ（神翼のフェイト） | R-PU-IMAGE | Fayt (神翼のフェイト) `cp0301_b04a` |
| 2020-09-17 | gacha_pickup_role_0494 +19 | 10連10ステップ目PU1体確定衣装コンテスト2018 ステップ1 | R-PU-BANNERART | ヒーローベルダ `cp0005_b03a`, ナースフィオーレ `cp0504_b02a` |
| 2020-09-19 | gacha_pickup_role_0504 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | Nel (華王妃ネル) `cp0305_b06a`, Clair (華王妃クレア) `cp0312_b06a` |
| 2020-10-03 | gacha_pickup_role_0508 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | エリス (天翼のエリス) `cp0113_b02a`, Miki (甘恋のミキ) `cp0502_b05a` |
| 2020-10-08 | gacha_pickup_role_0509 | ピックアップキャラガチャ（メイドレイミ/執事エイルマット） | R-PU-IMAGE | Reimi (メイドレイミ) `cp0402_b07a`, エイルマット (執事エイルマット) `cp0409_b02a` |
| 2020-10-08 | gacha_pickup_role_0510 +19 | 10連10ステップ目PU1体確定メイド1 ステップ1 | R-PU-BANNERART | Maid Nel `cp0305_b03a`, Maid Clair `cp0312_b03a` |
| 2020-10-08 | gacha_pickup_role_0520 +19 | 10連10ステップ目PU1体確定メイド2 ステップ1 | R-PU-BANNERART | 執事のレオン `cp0208_b02a`, メイドのソフィア `cp0302_b04a` |
| 2020-10-12 | gacha_pickup_role_0530 | 復刻テイルズ オブ ザ レイズコラボ PUガチャ\n(クレス/ミント) | R-PU-IMAGE | クレス `cc0030_b01a`, ミント `cc0031_b01a` |
| 2020-10-15 | gacha_pickup_role_0531 +19 | 10連10ステップ目PU1体確定メイド3 ステップ1 | R-PU-SIBLING | ヴァルカ (メイドヴァルカ) `cp0016_b02a`, Fiore (メイドフィオーレ) `cp0504_b05a` |
| 2020-10-15 | gacha_pickup_role_0541 +19 | 復刻ハロウィン1/10連10ステップ目PU1体確定 ステップ1 | R-PU-THEME | Were-Millie `cp0102_b02a`, Devil Clair `cp0312_b02a`, Vampire Victor `cp0503_b02a` |
| 2020-10-22 | gacha_pickup_role_0552 | ピックアップキャラガチャ（吸血鬼マリア/奇術師スフレ） | R-PU-IMAGE | Maria (吸血鬼マリア) `cp0303_b08a`, スフレ (奇術師スフレ) `cp0308_b02a` |
| 2020-10-29 | gacha_pickup_role_0553 | ロールピックアップキャラガチャ キャスター | R-PU-IMAGE | ペリシー (雪猫ペリシー) `cp0112_b03a`, 花嫁ミラージュ `cp0310_b03a`, 凛花リムル `cp0404_b02a` |
| 2020-10-29 | gacha_pickup_role_0554 +19 | 復刻ハロウィン2/10連10ステップ目PU1体確定ガチャステップ1 | R-PU-THEME | 堕天使ネル `cp0305_b04a`, 狼アルベル `cp0306_b03a`, 包帯フィオーレ `cp0504_b04a`, かぼちゃリリア `cp0507_b02a` |
| 2020-11-05 | gacha_pickup_role_0566 +19 | 復刻おとぎ世界/10連10ステップ目PU1体確定ステップ1 | R-PU-IMAGE | Evelysse (魔女イヴリーシュ) `cp0002_b08a`, Precis (魔改のプリシス) `cp0205_b05a`, Faize (祓魔師フェイズ) `cp0403_b02a` |
| 2020-11-07 | gacha_pickup_role_0576 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | Evelysse (泉郷イヴリーシュ) `cp0002_b09a`, Rena (泉郷レナ) `cp0202_b08a` |
| 2020-11-12 | gacha_pickup_role_0577 | ピックアップキャラガチャ(神翼のマリア/賢神のマスティマ) | R-PU-IMAGE | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2020-11-12 | gacha_pickup_role_0578 | ピックアップキャラガチャ(神龍のアシュトン) | R-PU-IMAGE | Ashton (神龍のアシュトン) `cp0204_b04a` |
| 2020-11-12 | gacha_pickup_role_0579 +9 | 10連10ステップ目PU1体確定　ステップ1(神龍のアシュトン) | R-PU-IMAGE | Ashton (神龍のアシュトン) `cp0204_b04a` |
| 2020-11-19 | gacha_pickup_role_0592 +19 | 復刻2019アニバーサリー/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | Verda (輪舞曲のベルダ) `cp0005_b05a`, 刻星のティカ (円舞曲のティカ) `cp0011_b03a` |
| 2020-11-26 | gacha_pickup_role_0603 | ピックアップキャラガチャ(歌星レナ/歌星フェイト) | R-PU-IMAGE | Rena (歌星レナ) `cp0202_b10a`, Fayt (歌星フェイト) `cp0301_b05a` |
| 2020-12-05 | gacha_pickup_role_0625 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | カーリン (狐将のカーリン) `cp0015_b05a`, リカルド (砲甲のリカルド) `cp0018_b03a` |
| 2020-12-10 | gacha_pickup_role_0626 | ピックアップエクシードキャラガチャ(黒のイヴリーシュ) | R-PU-IMAGE | Evelysse (黒のイヴリーシュ) `cp0002_b10a` |
| 2020-12-10 | gacha_pickup_role_0627 +9 | 復刻xmas2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | ペリシー (雪猫ペリシー) `cp0112_b03a`, Maria (銀雪マリア) `cp0303_b06a` |
| 2020-12-17 | gacha_pickup_role_0637 | ピックアップキャラガチャ(雪狐カーリン/聖夜ネル) | R-PU-IMAGE | カーリン (雪狐カーリン) `cp0015_b07a`, Nel (聖夜ネル) `cp0305_b08a` |
| 2020-12-17 | gacha_pickup_role_0638 +19 | 復刻xmas2018/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 雪花レナ `cp0202_b05a`, 雪空アシュトン `cp0204_b03a`, 聖夜クレア `cp0312_b05a` |
| 2020-12-24 | gacha_pickup_role_0648 | イヴリーシュ誕生日記念ガチャ | R-PU-BANNERART | Bride Eve `cp0002_b03a`, 渚のイヴリーシュ `cp0002_b05a`, 迎春イヴリーシュ `cp0002_b06a`, 歌星イヴリーシュ `cp0002_b07a`, Evelysse (魔女イヴリーシュ) `cp0002_b08a`, Evelysse (泉郷イヴリーシュ) `cp0002_b09a` |
| 2020-12-24 | gacha_pickup_role_0649 +19 | 復刻xmas2017/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Winter Evelysse `cp0002_b04a`, Holiday Precis `cp0205_b02a`, Winter Fidel `cp0501_b02a` |
| 2020-12-26 | gacha_pickup_role_0659 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2021-01-01 | gacha_pickup_role_0660 | ピックアップキャラガチャ(初春ティカ/初夢ラヴァーニア) | R-PU-IMAGE | 刻星のティカ (初春ティカ) `cp0011_b05a`, 初夢ラヴァーニア `cp0022_b03a` |
| 2021-01-01 | gacha_pickup_role_0661 +9 | 復刻正月2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | カーリン (暁狐のカーリン) `cp0015_b04a`, Reimi (鳳弓のレイミ) `cp0402_b06a` |
| 2021-01-02 | gacha_pickup_role_0671 +19 | 復刻正月2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 迎春イヴリーシュ `cp0002_b06a`, 迎春ティカ `cp0010_b02a` |
| 2021-01-09 | gacha_pickup_role_0681 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | 刻星のティカ (花嫁ティカ) `cp0011_b04a`, カーリン (花嫁カーリン) `cp0015_b06a` |
| 2021-01-14 | gacha_pickup_role_0682 | ピックアップキャラガチャ(神弓のレイミ) | R-PU-IMAGE | Reimi (神弓のレイミ) `cp0402_b08a` |
| 2021-01-14 | gacha_pickup_role_0683 +9 | 10連10ステップ目PU1体確定　ステップ1(神弓のレイミ) | R-PU-IMAGE | Reimi (神弓のレイミ) `cp0402_b08a` |
| 2021-01-14 | gacha_pickup_role_0693 +19 | 復刻SRF/10連10ステップ目PU1体確定　ステップ1 | R-PU-RERUN | ＳＲＦフェイト `cp0301_b03a`, ＳＲＦソフィア `cp0302_b05a` |
| 2021-01-21 | gacha_paid_role_exLucifer_202101 | ユニバースパスPUキャラガチャ（2021/01） | R-PU-IMAGE | Luther A (ルシファー) `cm405_b02g` |
| 2021-01-21 | gacha_pickup_role_0703 | ピックアップエクシードキャラガチャ(ルシファー) | R-PU-IMAGE | Luther A (ルシファー) `cm405_b02g` |
| 2021-01-28 | gacha_pickup_role_0706 | ピックアップキャラガチャ(甘恋のミリー/甘砲のプリシス) | R-PU-IMAGE | Millie (甘恋のミリー) `cp0102_b04a`, Precis (甘砲のプリシス) `cp0205_b06a` |
| 2021-01-28 | gacha_pickup_role_0707 +19 | 復刻バレンタイン2018/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Sweet Verda `cp0005_b02a`, Cat Rena `cp0202_b03a`, Dream Welch `cp0508_b03a` |
| 2021-02-01 | gacha_pickup_role_0718 +9 | 復刻バレンタイン2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | エリス (天翼のエリス) `cp0113_b02a`, Miki (甘恋のミキ) `cp0502_b05a` |
| 2021-02-04 | gacha_pickup_role_0728 +9 | 復刻バレンタイン2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | 甘狐のカーリン `cp0015_b02a`, 天真のペリシー `cp0112_b02a`, 凛花リムル `cp0404_b02a` |
| 2021-02-06 | gacha_pickup_role_0738 | 週末限定ピックアップキャラガチャ | R-PU-IMAGE | Verda (常夏のベルダ) `cp0005_b06a`, Clair (常夏のクレア) `cp0312_b07a` |
| 2021-02-20 | gacha_pickup_role_0744 | 週末限定ピックアップキャラガチャ | R-PU-GROUP | ユーイン (真夏のユーイン) `cp0013_b02a`, ウェルチ (真夏のウェルチ) `cp0014_b02a` |
| 2021-02-25 | gacha_pickup_role_0749 +9 | 復刻春節2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | Nel (華王妃ネル) `cp0305_b06a`, Clair (華王妃クレア) `cp0312_b06a` |
| 2021-03-04 | gacha_pickup_role_0759 +9 | 復刻泉郷2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | Evelysse (泉郷イヴリーシュ) `cp0002_b09a`, Rena (泉郷レナ) `cp0202_b08a` |
| 2021-03-06 | gacha_pickup_role_0769 | 週末限定ピックアップキャラガチャ | R-PU-GROUP | 渚のラヴァーニア `cp0022_b02a`, エリス (渚のエリス) `cp0113_b03a` |
| 2021-03-11 | gacha_pickup_role_0771 | ピックアップキャラガチャ(神導のソフィア) | R-PU-IMAGE | Sophia (神導のソフィア) `cp0302_b07a` |
| 2021-03-11 | gacha_pickup_role_0772 +9 | 10連10ステップ目PU1体確定　ステップ1(神導のソフィア) | R-PU-IMAGE | Sophia (神導のソフィア) `cp0302_b07a` |
| 2021-03-18 | gacha_paid_role_gaburieru_202103 | ユニバースパスPUキャラガチャ（2021/03） | R-PU-IMAGE | ガブリエル `cm506_b01a` |
| 2021-03-18 | gacha_pickup_role_0783 | ピックアップエクシードキャラガチャ(ガブリエル) | R-PU-IMAGE | ガブリエル `cm506_b01a` |
| 2021-03-18 | gacha_pickup_role_0784 | 復刻ピックアップキャラガチャ(神翼のマリア/賢神のマスティマ) | R-PU-IMAGE | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2021-03-25 | gacha_pickup_role_0805 | ピックアップキャラガチャ(歌星カーリン/歌星ティカ) | R-PU-GROUP | 刻星のティカ (歌星ティカ) `cp0011_b06a`, カーリン (歌星カーリン) `cp0015_b08a` |
| 2021-03-25 | gacha_pickup_role_0806 | 復刻ピックアップキャラガチャ(メイドレイミ/執事エイルマット) | R-PU-IMAGE | Reimi (メイドレイミ) `cp0402_b07a`, エイルマット (執事エイルマット) `cp0409_b02a` |
| 2021-03-31 | gacha_pickup_role_0838 | 復刻ピックアップキャラガチャ(歌星レナ/歌星フェイト) | R-PU-IMAGE | Rena (歌星レナ) `cp0202_b10a`, Fayt (歌星フェイト) `cp0301_b05a` |
| 2021-04-08 | gacha_pickup_role_0840 +9 | 復刻狐将/砲甲2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | カーリン (狐将のカーリン) `cp0015_b05a`, リカルド (砲甲のリカルド) `cp0018_b03a` |
| 2021-04-08 | gacha_pickup_role_0850 +9 | 復刻鬼炎/斬鬼2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | Nel (斬鬼のネル) `cp0305_b07a`, Albel (鬼炎のアルベル) `cp0306_b04a` |
| 2021-05-06 | gacha_pickup_role_0911 +9 | 復刻桜花桜雲/10連10ステップ目PU1体確定　ステップ1 | R-PU-RERUN | Blossom Dias `cp0207_b02a`, Blossom Maria `cp0303_b03a` |
| 2021-05-06 | gacha_pickup_role_0921 +9 | 復刻メイド2018/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 執事のレオン `cp0208_b02a`, メイドのソフィア `cp0302_b04a`, Maid Nel `cp0305_b03a`, Maid Clair `cp0312_b03a` |
| 2021-05-06 | gacha_pickup_role_0971 +9 | 復刻兎耳/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | 兎耳のマリア `cp0303_b05a`, 兎耳のミラージュ `cp0310_b02a` |
| 2021-05-06 | gacha_pickup_role_0991 +9 | 復刻アイドル2018/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 歌星ベルダ `cp0005_b04a`, 歌星レイミ `cp0402_b05a`, 歌星ミキ `cp0502_b04a` |
| 2021-05-20 | gacha_pickup_role_1031 +9 | 復刻バレンタイン2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | 甘狐のカーリン `cp0015_b02a`, 天真のペリシー `cp0112_b02a`, 凛花リムル `cp0404_b02a` |
| 2021-05-20 | gacha_pickup_role_1041 +9 | 復刻アイドル2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 歌星イヴリーシュ `cp0002_b07a`, 歌星ソフィア `cp0302_b06a` |
| 2021-05-20 | gacha_pickup_role_1081 +9 | 復刻メイド2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | ヴァルカ (メイドヴァルカ) `cp0016_b02a`, Fiore (メイドフィオーレ) `cp0504_b05a` |
| 2021-05-20 | gacha_pickup_role_1111 +9 | 復刻クリスマス2019/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | ペリシー (雪猫ペリシー) `cp0112_b03a`, Maria (銀雪マリア) `cp0303_b06a` |
| 2021-06-03 | gacha_pickup_role_1121 +9 | 復刻正月2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | カーリン (暁狐のカーリン) `cp0015_b04a`, Reimi (鳳弓のレイミ) `cp0402_b06a` |
| 2021-06-03 | gacha_pickup_role_1131 +9 | 復刻春節2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | Nel (華王妃ネル) `cp0305_b06a`, Clair (華王妃クレア) `cp0312_b06a` |
| 2021-06-03 | gacha_pickup_role_1141 +9 | 復刻バレンタイン2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | エリス (天翼のエリス) `cp0113_b02a`, Miki (甘恋のミキ) `cp0502_b05a` |
| 2021-06-03 | gacha_pickup_role_1151 +9 | 復刻泉郷2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | Evelysse (泉郷イヴリーシュ) `cp0002_b09a`, Rena (泉郷レナ) `cp0202_b08a` |
| 2021-06-03 | gacha_pickup_role_1161 +9 | 復刻神級(1)/10連10ステップ目PU1体確定　ステップ1 | R-PU-BANNERART | マスティマ (賢神のマスティマ) `cp0019_b02a`, Maria (神翼のマリア) `cp0303_b07a` |
| 2021-06-03 | gacha_pickup_role_1171 +9 | 復刻神級(2)/10連10ステップ目PU1体確定　ステップ1 | R-PU-BANNERART | Rena (神星のレナ) `cp0202_b09a`, Ashton (神龍のアシュトン) `cp0204_b04a`, Fayt (神翼のフェイト) `cp0301_b04a` |
| 2021-06-03 | gacha_pickup_role_1181 +9 | 復刻狐将砲甲/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | カーリン (狐将のカーリン) `cp0015_b05a`, リカルド (砲甲のリカルド) `cp0018_b03a` |
| 2021-06-03 | gacha_pickup_role_1191 +9 | 復刻鬼炎斬鬼/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | Nel (斬鬼のネル) `cp0305_b07a`, Albel (鬼炎のアルベル) `cp0306_b04a` |
| 2021-06-03 | gacha_pickup_role_1201 +9 | 復刻花嫁2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 刻星のティカ (花嫁ティカ) `cp0011_b04a`, カーリン (花嫁カーリン) `cp0015_b06a` |
| 2021-06-03 | gacha_pickup_role_1211 +9 | 復刻水着2020(1)/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | Verda (常夏のベルダ) `cp0005_b06a`, Clair (常夏のクレア) `cp0312_b07a` |
| 2021-06-03 | gacha_pickup_role_1221 +9 | 復刻水着2020(2)/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | ユーイン (真夏のユーイン) `cp0013_b02a`, ウェルチ (真夏のウェルチ) `cp0014_b02a` |
| 2021-06-03 | gacha_pickup_role_1231 +9 | 復刻水着2020(3)/10連10ステップ目PU1体確定　ステップ1 | R-PU-SIBLING | 渚のラヴァーニア `cp0022_b02a`, エリス (渚のエリス) `cp0113_b03a` |
| 2021-06-03 | gacha_pickup_role_1241 +9 | 復刻メイド2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Reimi (メイドレイミ) `cp0402_b07a`, エイルマット (執事エイルマット) `cp0409_b02a` |
| 2021-06-03 | gacha_pickup_role_1251 +9 | 復刻ハロウィン2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Maria (吸血鬼マリア) `cp0303_b08a`, スフレ (奇術師スフレ) `cp0308_b02a` |
| 2021-06-03 | gacha_pickup_role_1261 +9 | 復刻アイドル2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Rena (歌星レナ) `cp0202_b10a`, Fayt (歌星フェイト) `cp0301_b05a` |
| 2021-06-03 | gacha_pickup_role_1271 +9 | 復刻クリスマス2020/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | カーリン (雪狐カーリン) `cp0015_b07a`, Nel (聖夜ネル) `cp0305_b08a` |
| 2021-06-10 | gacha_pickup_role_1281 +9 | 復刻正月2021/10連10ステップ目PU1体確定 ステップ1 | R-PU-THEME | 刻星のティカ (初春ティカ) `cp0011_b05a`, 初夢ラヴァーニア `cp0022_b03a` |
| 2021-06-10 | gacha_pickup_role_1291 +9 | 復刻神級(3)/10連10ステップ目PU1体確定 ステップ1 | R-PU-BANNERART | Sophia (神導のソフィア) `cp0302_b07a`, Reimi (神弓のレイミ) `cp0402_b08a` |
| 2021-06-10 | gacha_pickup_role_1301 +9 | 復刻バレンタイン2021/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | Millie (甘恋のミリー) `cp0102_b04a`, Precis (甘砲のプリシス) `cp0205_b06a` |
| 2021-06-10 | gacha_pickup_role_1311 +9 | 復刻アイドル2021/10連10ステップ目PU1体確定　ステップ1 | R-PU-THEME | 刻星のティカ (歌星ティカ) `cp0011_b06a`, カーリン (歌星カーリン) `cp0015_b08a` |
| 2021-06-10 | gacha_pickup_role_1321 +9 | 復刻エクシードキャラ/10連10ステップ目PU1体確定　ステップ1 | R-PU-IMAGE | Luther A (ルシファー) `cm405_b02g`, ガブリエル `cm506_b01a`, Evelysse (黒のイヴリーシュ) `cp0002_b10a` |

</details>
<!-- END GENERATED -->
