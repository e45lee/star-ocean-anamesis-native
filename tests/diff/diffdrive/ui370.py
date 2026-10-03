"""The 3.7.0 UI's tap points at 729x1296 (window pixels), by name (PLAN-consolidate D7). Taken from
emulator/scripts/emulator_session.sh, summer_demo.sh and the port's session scripts, which use the
same points on both programs."""
TITLE = "364:713"            # TAP TO START (anywhere on the title), also a communication dialog's リトライ
DATA_DECIDE = "364:1043"     # Episodeデータ管理 -> 決定 (the data check's first dialog)
DATA_DOWNLOAD = "515:800"    # the download dialog's ダウンロード
DATA_DONE = "364:790"        # the download's 完了
TERMS_AGREE = "364:689"      # the new player's terms: 同意する
NAME_FIELD = "364:647"       # the name dialog's field (opens the keyboard)
NAME_DECIDE = "364:790"      # the name dialog's 決定
HOME_MISSION = "270:1085"    # home: ミッション
HOME_EVENT = "90:1085"       # home: イベント
FOOTER_HOME = "60:1245"      # the footer's ホーム
FOOTER_GACHA = "425:1250"    # the footer's ガチャ
PLANET_MERE = "660:520"      # the planet select: Mere
PLANET_SORTIE = "587:795"    # the planet select: 出撃
MAP_105 = "363:665"          # Mere's mission map: 1-05 (mf01_001)
SINGLE_PLAY = "364:905"      # a mission's detail: シングルプレイ開始
RENTAL_NONE = "620:1120"     # the rental list: 選択しない
PARTY_START = "364:900"      # the party: ミッション開始
CONFIRM_OK = "515:712"       # the start confirmation: 決定
RESULT_OK = "510:1040"       # the Mission Result pages: OK
STORY_SKIP = "115:1240"      # a story scene: スキップ
STORY_SKIP_YES = "515:742"   # the skip dialog: はい
STORY_START = "515:715"      # a story's detail: ストーリー開始
BACK = "100:1120"            # 戻る (the event board)
GACHA_TAB_RECOMMENDED = "100:175"
GACHA_FIRST_BANNER = "360:320"
GACHA_10 = "540:945"         # 10連ガチャ
GACHA_DECIDE = "515:800"     # the draw confirmation: 決定
SUMMON_START = "364:1190"    # 召喚開始
SUMMON_REVEAL = "364:650"
SUMMON_ALL_SKIP = "577:1199"
GACHA_RESULT_NEXT = "364:1002"  # the result list's 次へ, then 閉じる at the same spot
