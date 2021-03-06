<?php

/**
 * 「和暦(二十四節気 / 七十二候)と江戸の不定時法(時鐘 / 辰刻)を取得する
 *
 * イミュータブル(不変)なインスタンスなので、データを取得することしかできません
<pre>
http://www.nnh.to/yomikata/72kou.html より参照
一部
https://ja.wikipedia.org/wiki/%E4%B8%83%E5%8D%81%E4%BA%8C%E5%80%99
で補完
<pre>
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 **/

class wareki {

//public:
/**
 * 不定時法(時鐘)を取得
 *
 * @access public
 * @return string 時鐘
 */
  public function get_時鐘() { return $this->時鐘_; }
  protected function set_時鐘($v) { $this->時鐘_ = $v; }

/**
 * 不定時法(辰刻)を取得
 *
 * @access public
 * @return string 辰刻
 */
  public function get_辰刻() { return $this->辰刻_; }
  protected function set_辰刻($v) { $this->辰刻_ = $v; }

/**
 * 暦の開始日通算を取得
 *
 * @access public
 * @return int 開始日通算
 */
  public function get_開始日通算() { return $this->開始日通算_; }
  protected function set_開始日通算($v) { $this->開始日通算_ = $v; }

  // 開始日確認
  public function get_開始日確認() { return $this->開始日確認_; }
  protected function set_開始日確認($v) { $this->開始日確認_ = $v; }

/**
 * 暦の終了日通算を取得
 *
 * @access public
 * @return int 終了日通算
 */
  // 終了日通算
  public function get_終了日通算() { return $this->終了日通算_; }
  protected function set_終了日通算($v) { $this->終了日通算_ = $v; }

  // 終了日確認
  public function get_終了日確認() { return $this->終了日確認_; }
  protected function set_終了日確認($v) { $this->終了日確認_ = $v; }

/**
 * 二十四節気を取得
 *
 * @access public
 * @return string 二十四節気
 */
  public function get_二十四節気() { return $this->二十四節気_; }
  protected function set_二十四節気($v) { $this->二十四節気_ = $v; }

/**
 * 候を取得
 *
 * @access public
 * @return string 候
 */
  public function get_候() { return $this->候_; }
  protected function set_候($v) { $this->候_ = $v; }

/**
 * 七十二候を取得
 *
 * @access public
 * @return string 七十二候
 */
  public function get_七十二候() { return $this->七十二候_; }
  protected function set_七十二候($v) { $this->七十二候_ = $v; }

/**
 * 七十二候開きを取得
 *
 * 文字的に「表示されるか不明な文字」が七十二候にあるので、そのとき用の代替え文字。問題なければ七十二候と同じ文字列
 *
 * @access public
 * @return string 七十二候開き
 */
  public function get_七十二候開き() { return $this->七十二候開き_; }
  protected function set_七十二候開き($v) { $this->七十二候開き_ = $v; }

/**
 * 七十二候読みを取得
 *
 * 七十二候の読み仮名
 *
 * @access public
 * @return string 七十二候読み
 */
  public function get_七十二候読み() { return $this->七十二候読み_; }
  protected function set_七十二候読み($v) { $this->七十二候読み_ = $v; }

/**
 * 七十二候意味を取得
 *
 * 七十二候の簡単な解説
 *
 * @access public
 * @return string 七十二候意味
 */
  public function get_七十二候意味() { return $this->七十二候意味_; }
  protected function set_七十二候意味($v) { $this->七十二候意味_ = $v; }


/**
 * インスタンス作成
 *
 * インスタンス作成のタイミングで「全ての情報」が作成されます。このインスタンスはイミュータブル(不変)です。
 *
 * @access public
 */
public function __construct() {
  // とりあえず
  date_default_timezone_set('Asia/Tokyo');

  // まず「今」を把握
  $t = time();
//$t = strtotime('2015-3-1 00:00:00'); // 閏年減算確認
//$t = strtotime('2016-3-1 00:00:00'); // 閏年減算確認
//$t = strtotime('2016-2-29 00:00:00'); // 閏年減算確認
//$t = strtotime('2016-1-4 00:00:00'); // 軽く確認
//$t = strtotime('2016-2-29 00:00:00'); // 閏年確認
//$t = strtotime('2016-3-1 00:00:00'); // 閏年確認
//$t = strtotime('2016-1-30 00:00:00'); // 七十二候開き確認

//$t = strtotime('2016-1-30 06:42:56'); // 時刻：日の入り前
//$t = strtotime('2016-1-30 06:42:57'); // 時刻：日中
//$t = strtotime('2016-1-30 08:29:57'); // 時刻：日中
//$t = strtotime('2016-1-30 17:05:19'); // 時刻：日の入り直前
//$t = strtotime('2016-1-30 17:05:10'); // 時刻：日の入り直前
//$t = strtotime('2016-1-30 17:05:20'); // 時刻：日の入り以降

  // 日付から二十四節季と七十二候を把握
  list($day_of, $leap_year) = explode(' ', date('z L', $t));
//var_dump($day_of);
//var_dump($leap_year);

  // XXX 閏年でかつ2/29移行なら、計算を楽にしたいので一旦減算する
  if ( (1 == $leap_year) && (59 <= $day_of) ) {
    $day_of --;
  }
//var_dump($day_of);

  // 季節情報取得
  $season_info = $this->season_infomation_get((int)$day_of);
//var_dump($season_info);

  // 時刻情報取得
  $time_info = $this->time_infomation_get($t);
//var_dump($time_info);

  // ざっくりと設定
  foreach(['season_info', 'time_info'] as $data) {
    foreach($$data as $k => $v) {
      //
      $m = 'set_' . $k;
      $this->$m($v);
    }
  }
}

// 時刻情報取得
protected function time_infomation_get($t) {
  $edo_t_data_daytime = array(
    array('時鐘' => '卯の刻', '辰刻' => '明六ツ'),
    array('時鐘' => '卯の刻', '辰刻' => '明六ツ半'),
    array('時鐘' => '辰の刻', '辰刻' => '朝五ツ'),
    array('時鐘' => '辰の刻', '辰刻' => '朝五ツ半'),
    array('時鐘' => '巳の刻', '辰刻' => '朝四ツ'),
    array('時鐘' => '巳の刻', '辰刻' => '朝四ツ半'),
    array('時鐘' => '午の刻', '辰刻' => '昼九ツ'),
    array('時鐘' => '午の刻', '辰刻' => '昼九ツ半'),
    array('時鐘' => '羊の刻', '辰刻' => '昼ハツ'),
    array('時鐘' => '羊の刻', '辰刻' => '昼ハツ半'),
    array('時鐘' => '申の刻', '辰刻' => '夕七ツ'),
    array('時鐘' => '申の刻', '辰刻' => '夕七ツ半'),
  );
  $edo_t_data_ight = array(
    array('時鐘' => '酉の刻', '辰刻' => '暮六ツ'),
    array('時鐘' => '酉の刻', '辰刻' => '暮六ツ半'),
    array('時鐘' => '戌の刻', '辰刻' => '宵五ツ'),
    array('時鐘' => '戌の刻', '辰刻' => '宵五ツ半'),
    array('時鐘' => '亥の刻', '辰刻' => '夜四ツ'),
    array('時鐘' => '亥の刻', '辰刻' => '夜四ツ半'),
    array('時鐘' => '子の刻', '辰刻' => '夜九ツ'),
    array('時鐘' => '子の刻', '辰刻' => '夜九ツ半'),
    array('時鐘' => '丑の刻', '辰刻' => '夜八ツ'),
    array('時鐘' => '丑の刻', '辰刻' => '夜八ツ半'),
    array('時鐘' => '寅の刻', '辰刻' => '暁七ツ'),
    array('時鐘' => '寅の刻', '辰刻' => '暁七ツ半'),
  );
  // とりあえず江戸城跡あたりに設定
  $latitude = 35.684468;
  $longitude = 139.753576;

  // 本日の日の出日の入りの時刻を取得
  $sunrise = date_sunrise($t, SUNFUNCS_RET_TIMESTAMP, $latitude, $longitude);
  $sunset = date_sunset($t, SUNFUNCS_RET_TIMESTAMP, $latitude, $longitude);
  // 明け前用に「昨日の日の入り」の時刻を把握
  $t2 = strtotime("-1 days", $t);
  $yesterday_sunset = date_sunset($t2, SUNFUNCS_RET_TIMESTAMP, $latitude, $longitude);
  // 暮れ用に「明日の日の出」の時刻を把握
  $t2 = strtotime("+1 days", $t);
  $tomorrow_sunrise = date_sunrise($t2, SUNFUNCS_RET_TIMESTAMP, $latitude, $longitude);
/*
var_dump($t);
var_dump($yesterday_sunset);
var_dump($sunrise);
var_dump($sunset);
var_dump($tomorrow_sunrise);
echo date("Y-m-d H:i:s\n", $yesterday_sunset);
echo date("Y-m-d H:i:s\n", $sunrise);
echo date("Y-m-d H:i:s\n", $sunset);
echo date("Y-m-d H:i:s\n", $tomorrow_sunrise);
*/

  // 「今日の日の出よりも前」の処理
  if ($t <= $sunrise) {
//echo "日の出より前\n";
    $base = $yesterday_sunset;
    $一刻 = $sunrise - $yesterday_sunset;
    $array_name = 'edo_t_data_ight';
  } else
  // 「今日の日の出～今日の日の入り」の処理
  if ($t <= $sunset) {
//echo "日中\n";
    $base = $sunrise;
    $一刻 = $sunset - $sunrise;
    $array_name = 'edo_t_data_daytime';
  } else
  // 「今日の日の入り以降」の処理
  {
//echo "日の入り以降\n";
    $base = $sunset;
    $一刻 = $tomorrow_sunrise - $sunset;
    $array_name = 'edo_t_data_ight';
  }
  // 「一刻(の半分、実際には)の時間幅」を計算
  $一刻 = $一刻 / 12;
/*
echo "\n";
var_dump($base);
var_dump($一刻);
*/
  // 係数を計算
  $edo_t = (int)(($t - $base) / $一刻);
  // XXX わずかに端数処理があるので、12になったら11に切り下げる
  if (11 < $edo_t) {
    $edo_t = 11;
  }
/*
var_dump($edo_t);
var_dump($$array_name[$edo_t]);
*/

  //
  return $$array_name[$edo_t];
}


// 季節情報取得
protected function season_infomation_get($day_of) {
  //
  $ret = [];
  //
  switch($day_of) {
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
      $ret['開始日通算'] = 34;
      $ret['開始日確認'] = '02/04';
      $ret['終了日通算'] = 38;
      $ret['終了日確認'] = '02/08';
      $ret['二十四節気'] = '立春';
      $ret['候']         = '初候';
      $ret['七十二候']     = '東風解凍';
      $ret['七十二候開き'] = '東風解凍';
      $ret['七十二候読み'] = 'はるかぜこおりをとく';
      $ret['七十二候意味'] = '東風が厚い氷を解かし始める';
      break;

    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
      $ret['開始日通算'] = 39;
      $ret['開始日確認'] = '02/09';
      $ret['終了日通算'] = 43;
      $ret['終了日確認'] = '02/13';
      $ret['二十四節気'] = '立春';
      $ret['候']         = '次候';
      $ret['七十二候']     = '黄鶯?睆';
      $ret['七十二候開き'] = '黄鶯[目見][目完]';
      $ret['七十二候読み'] = 'おうこうけんかんす';
      $ret['七十二候意味'] = 'うぐいすが山里で鳴き始める';
      break;

    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
      $ret['開始日通算'] = 44;
      $ret['開始日確認'] = '02/14';
      $ret['終了日通算'] = 48;
      $ret['終了日確認'] = '02/18';
      $ret['二十四節気'] = '立春';
      $ret['候']         = '末候';
      $ret['七十二候']     = '魚上氷';
      $ret['七十二候開き'] = '魚上氷';
      $ret['七十二候読み'] = 'うおこおりをはいずる';
      $ret['七十二候意味'] = '割れた氷の間から魚が飛び出る';
      break;

    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
      $ret['開始日通算'] = 49;
      $ret['開始日確認'] = '02/19';
      $ret['終了日通算'] = 53;
      $ret['終了日確認'] = '02/23';
      $ret['二十四節気'] = '雨水';
      $ret['候']         = '初候';
      $ret['七十二候']     = '土脉潤起';
      $ret['七十二候開き'] = '土脉潤起';
      $ret['七十二候読み'] = 'つちのしょううるおいおこる';
      $ret['七十二候意味'] = '雨が降って土が湿り気を含む';
      break;

    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
      $ret['開始日通算'] = 54;
      $ret['開始日確認'] = '02/24';
      $ret['終了日通算'] = 58;
      $ret['終了日確認'] = '02/28';
      $ret['二十四節気'] = '雨水';
      $ret['候']         = '次候';
      $ret['七十二候']     = '霞始靆';
      $ret['七十二候開き'] = '霞始靆';
      $ret['七十二候読み'] = 'かすみはじめてたなびく';
      $ret['七十二候意味'] = '霞がたなびき始める';
      break;

    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
      $ret['開始日通算'] = 59;
      $ret['開始日確認'] = '03/01';
      $ret['終了日通算'] = 63;
      $ret['終了日確認'] = '03/05';
      $ret['二十四節気'] = '雨水';
      $ret['候']         = '末候';
      $ret['七十二候']     = '草木萠動';
      $ret['七十二候開き'] = '草木萠動';
      $ret['七十二候読み'] = 'そうもくめばえいずる';
      $ret['七十二候意味'] = '草木が芽吹き始める';
      break;

    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
      $ret['開始日通算'] = 64;
      $ret['開始日確認'] = '03/06';
      $ret['終了日通算'] = 68;
      $ret['終了日確認'] = '03/10';
      $ret['二十四節気'] = '啓蟄';
      $ret['候']         = '初候';
      $ret['七十二候']     = '蟄虫啓戸';
      $ret['七十二候開き'] = '蟄虫啓戸';
      $ret['七十二候読み'] = 'すごもりむしとをひらく';
      $ret['七十二候意味'] = '冬ごもりの虫が出てくる';
      break;

    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
      $ret['開始日通算'] = 69;
      $ret['開始日確認'] = '03/11';
      $ret['終了日通算'] = 73;
      $ret['終了日確認'] = '03/15';
      $ret['二十四節気'] = '啓蟄';
      $ret['候']         = '次候';
      $ret['七十二候']     = '桃始笑';
      $ret['七十二候開き'] = '桃始笑';
      $ret['七十二候読み'] = 'ももはじめてさく';
      $ret['七十二候意味'] = '桃の花が咲き始める';
      break;

    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
      $ret['開始日通算'] = 74;
      $ret['開始日確認'] = '03/16';
      $ret['終了日通算'] = 78;
      $ret['終了日確認'] = '03/20';
      $ret['二十四節気'] = '啓蟄';
      $ret['候']         = '末候';
      $ret['七十二候']     = '菜虫化蝶';
      $ret['七十二候開き'] = '菜虫化蝶';
      $ret['七十二候読み'] = 'なむしちょうとなる';
      $ret['七十二候意味'] = '青虫が羽化して紋白蝶になる';
      break;

    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
      $ret['開始日通算'] = 79;
      $ret['開始日確認'] = '03/21';
      $ret['終了日通算'] = 83;
      $ret['終了日確認'] = '03/25';
      $ret['二十四節気'] = '春分';
      $ret['候']         = '初候';
      $ret['七十二候']     = '雀始巣';
      $ret['七十二候開き'] = '雀始巣';
      $ret['七十二候読み'] = 'すずめはじめてすくう';
      $ret['七十二候意味'] = '雀が巣をかまえ始める';
      break;

    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
      $ret['開始日通算'] = 84;
      $ret['開始日確認'] = '03/26';
      $ret['終了日通算'] = 88;
      $ret['終了日確認'] = '03/30';
      $ret['二十四節気'] = '春分';
      $ret['候']         = '次候';
      $ret['七十二候']     = '桜始開';
      $ret['七十二候開き'] = '桜始開';
      $ret['七十二候読み'] = 'さくらはじめてひらく';
      $ret['七十二候意味'] = '桜の花が咲き始める';
      break;

    case 89:
    case 90:
    case 91:
    case 92:
    case 93:
      $ret['開始日通算'] = 89;
      $ret['開始日確認'] = '03/31';
      $ret['終了日通算'] = 93;
      $ret['終了日確認'] = '04/04';
      $ret['二十四節気'] = '春分';
      $ret['候']         = '末候';
      $ret['七十二候']     = '雷乃発声';
      $ret['七十二候開き'] = '雷乃発声';
      $ret['七十二候読み'] = 'かみなりすなわちこえをはっす';
      $ret['七十二候意味'] = '遠くで雷の声がし始める';
      break;

    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
      $ret['開始日通算'] = 94;
      $ret['開始日確認'] = '04/05';
      $ret['終了日通算'] = 98;
      $ret['終了日確認'] = '04/09';
      $ret['二十四節気'] = '清明';
      $ret['候']         = '初候';
      $ret['七十二候']     = '玄鳥至';
      $ret['七十二候開き'] = '玄鳥至';
      $ret['七十二候読み'] = 'つばめきたる';
      $ret['七十二候意味'] = 'つばめが南からやってくる';
      break;

    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
      $ret['開始日通算'] = 99;
      $ret['開始日確認'] = '04/10';
      $ret['終了日通算'] = 103;
      $ret['終了日確認'] = '04/14';
      $ret['二十四節気'] = '清明';
      $ret['候']         = '次候';
      $ret['七十二候']     = '鴻雁北';
      $ret['七十二候開き'] = '鴻雁北';
      $ret['七十二候読み'] = 'こうがんかえる';
      $ret['七十二候意味'] = '雁が北へ渡っていく';
      break;

    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
      $ret['開始日通算'] = 104;
      $ret['開始日確認'] = '04/15';
      $ret['終了日通算'] = 108;
      $ret['終了日確認'] = '04/19';
      $ret['二十四節気'] = '清明';
      $ret['候']         = '末候';
      $ret['七十二候']     = '虹始見';
      $ret['七十二候開き'] = '虹始見';
      $ret['七十二候読み'] = 'にじはじめてあらわる';
      $ret['七十二候意味'] = '雨の後に虹が出始める';
      break;

    case 109:
    case 110:
    case 111:
    case 112:
    case 113:
      $ret['開始日通算'] = 109;
      $ret['開始日確認'] = '04/20';
      $ret['終了日通算'] = 113;
      $ret['終了日確認'] = '04/24';
      $ret['二十四節気'] = '穀雨';
      $ret['候']         = '初候';
      $ret['七十二候']     = '葭始生';
      $ret['七十二候開き'] = '葭始生';
      $ret['七十二候読み'] = 'あしはじめてしょうず';
      $ret['七十二候意味'] = '葦が芽を吹き始める';
      break;

    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
      $ret['開始日通算'] = 114;
      $ret['開始日確認'] = '04/25';
      $ret['終了日通算'] = 118;
      $ret['終了日確認'] = '04/29';
      $ret['二十四節気'] = '穀雨';
      $ret['候']         = '次候';
      $ret['七十二候']     = '霜止出苗';
      $ret['七十二候開き'] = '霜止出苗';
      $ret['七十二候読み'] = 'しもやみてなえいずる';
      $ret['七十二候意味'] = '霜が終わり稲の苗が生長する';
      break;

    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
      $ret['開始日通算'] = 119;
      $ret['開始日確認'] = '04/30';
      $ret['終了日通算'] = 123;
      $ret['終了日確認'] = '05/04';
      $ret['二十四節気'] = '穀雨';
      $ret['候']         = '末候';
      $ret['七十二候']     = '牡丹華';
      $ret['七十二候開き'] = '牡丹華';
      $ret['七十二候読み'] = 'ぼたんはなさく';
      $ret['七十二候意味'] = '牡丹の花が咲く';
      break;

    case 124:
    case 125:
    case 126:
    case 127:
    case 128:
      $ret['開始日通算'] = 124;
      $ret['開始日確認'] = '05/05';
      $ret['終了日通算'] = 128;
      $ret['終了日確認'] = '05/09';
      $ret['二十四節気'] = '立夏';
      $ret['候']         = '初候';
      $ret['七十二候']     = '蛙始鳴';
      $ret['七十二候開き'] = '[圭/龜]始鳴';
      $ret['七十二候読み'] = 'かわずはじめてなく';
      $ret['七十二候意味'] = '蛙が鳴き始める';
      break;

    case 129:
    case 130:
    case 131:
    case 132:
    case 133:
      $ret['開始日通算'] = 129;
      $ret['開始日確認'] = '05/10';
      $ret['終了日通算'] = 133;
      $ret['終了日確認'] = '05/14';
      $ret['二十四節気'] = '立夏';
      $ret['候']         = '次候';
      $ret['七十二候']     = '蚯蚓出';
      $ret['七十二候開き'] = '蚯蚓出';
      $ret['七十二候読み'] = 'みみずいずる';
      $ret['七十二候意味'] = 'みみずが地上にはい出る';
      break;

    case 134:
    case 135:
    case 136:
    case 137:
    case 138:
    case 139:
      $ret['開始日通算'] = 134;
      $ret['開始日確認'] = '05/15';
      $ret['終了日通算'] = 139;
      $ret['終了日確認'] = '05/20';
      $ret['二十四節気'] = '立夏';
      $ret['候']         = '末候';
      $ret['七十二候']     = '竹笋生';
      $ret['七十二候開き'] = '竹笋生';
      $ret['七十二候読み'] = 'たけのこしょうず';
      $ret['七十二候意味'] = '竹の子が生えてくる';
      break;

    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
      $ret['開始日通算'] = 140;
      $ret['開始日確認'] = '05/21';
      $ret['終了日通算'] = 144;
      $ret['終了日確認'] = '05/25';
      $ret['二十四節気'] = '小満';
      $ret['候']         = '初候';
      $ret['七十二候']     = '蚕起食桑';
      $ret['七十二候開き'] = '蚕起食桑';
      $ret['七十二候読み'] = 'かいこおきてくわをはむ';
      $ret['七十二候意味'] = '蚕が桑を盛んに食べ始める';
      break;

    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
      $ret['開始日通算'] = 145;
      $ret['開始日確認'] = '05/26';
      $ret['終了日通算'] = 149;
      $ret['終了日確認'] = '05/30';
      $ret['二十四節気'] = '小満';
      $ret['候']         = '次候';
      $ret['七十二候']     = '紅花栄';
      $ret['七十二候開き'] = '紅花栄';
      $ret['七十二候読み'] = 'ばにばなさかう';
      $ret['七十二候意味'] = '紅花が盛んに咲く';
      break;

    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 155:
      $ret['開始日通算'] = 150;
      $ret['開始日確認'] = '05/31';
      $ret['終了日通算'] = 155;
      $ret['終了日確認'] = '06/05';
      $ret['二十四節気'] = '小満';
      $ret['候']         = '末候';
      $ret['七十二候']     = '麦秋至';
      $ret['七十二候開き'] = '麦秋至';
      $ret['七十二候読み'] = 'むぎのときいたる';
      $ret['七十二候意味'] = '麦が熟し麦秋[ばくしゅう]となる';
      break;

    case 156:
    case 157:
    case 158:
    case 159:
    case 160:
      $ret['開始日通算'] = 156;
      $ret['開始日確認'] = '06/06';
      $ret['終了日通算'] = 160;
      $ret['終了日確認'] = '06/10';
      $ret['二十四節気'] = '芒種';
      $ret['候']         = '初候';
      $ret['七十二候']     = '螳螂生';
      $ret['七十二候開き'] = '螳螂生';
      $ret['七十二候読み'] = 'かまきりしょうず';
      $ret['七十二候意味'] = '螳螂が生まれ出る';
      break;

    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
      $ret['開始日通算'] = 161;
      $ret['開始日確認'] = '06/11';
      $ret['終了日通算'] = 165;
      $ret['終了日確認'] = '06/15';
      $ret['二十四節気'] = '芒種';
      $ret['候']         = '次候';
      $ret['七十二候']     = '腐草為蛍';
      $ret['七十二候開き'] = '腐草為蛍';
      $ret['七十二候読み'] = 'かれたるくさほたるとなる';
      $ret['七十二候意味'] = '(腐った草の下から蛍が生ずる)';
      break;

    case 166:
    case 167:
    case 168:
    case 169:
    case 170:
      $ret['開始日通算'] = 166;
      $ret['開始日確認'] = '06/16';
      $ret['終了日通算'] = 170;
      $ret['終了日確認'] = '06/20';
      $ret['二十四節気'] = '芒種';
      $ret['候']         = '末候';
      $ret['七十二候']     = '梅子黄';
      $ret['七十二候開き'] = '梅子黄';
      $ret['七十二候読み'] = 'うめのみきなり';
      $ret['七十二候意味'] = '梅の実が黄ばんで熟す';
      break;

    case 171:
    case 172:
    case 173:
    case 174:
    case 175:
    case 176:
      $ret['開始日通算'] = 171;
      $ret['開始日確認'] = '06/21';
      $ret['終了日通算'] = 176;
      $ret['終了日確認'] = '06/26';
      $ret['二十四節気'] = '夏至';
      $ret['候']         = '初候';
      $ret['七十二候']     = '乃東枯';
      $ret['七十二候開き'] = '乃東枯';
      $ret['七十二候読み'] = 'なつかれくさかるる';
      $ret['七十二候意味'] = '夏枯草が枯れる';
      break;

    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
      $ret['開始日通算'] = 177;
      $ret['開始日確認'] = '06/27';
      $ret['終了日通算'] = 181;
      $ret['終了日確認'] = '07/01';
      $ret['二十四節気'] = '夏至';
      $ret['候']         = '次候';
      $ret['七十二候']     = '菖蒲華';
      $ret['七十二候開き'] = '菖蒲華';
      $ret['七十二候読み'] = 'あやめはなさく';
      $ret['七十二候意味'] = 'あやめの花が咲く';
      break;

    case 182:
    case 183:
    case 184:
    case 185:
    case 186:
      $ret['開始日通算'] = 182;
      $ret['開始日確認'] = '07/02';
      $ret['終了日通算'] = 186;
      $ret['終了日確認'] = '07/06';
      $ret['二十四節気'] = '夏至';
      $ret['候']         = '末候';
      $ret['七十二候']     = '半夏生';
      $ret['七十二候開き'] = '半夏生';
      $ret['七十二候読み'] = 'はんげしょうず';
      $ret['七十二候意味'] = 'からすびしゃくが生える';
      break;

    case 187:
    case 188:
    case 189:
    case 190:
    case 191:
      $ret['開始日通算'] = 187;
      $ret['開始日確認'] = '07/07';
      $ret['終了日通算'] = 191;
      $ret['終了日確認'] = '07/11';
      $ret['二十四節気'] = '小暑';
      $ret['候']         = '初候';
      $ret['七十二候']     = '温風至';
      $ret['七十二候開き'] = '温風至';
      $ret['七十二候読み'] = 'あつかぜいたる';
      $ret['七十二候意味'] = 'あたたかい風が吹いてくる';
      break;

    case 192:
    case 193:
    case 194:
    case 195:
    case 196:
      $ret['開始日通算'] = 192;
      $ret['開始日確認'] = '07/12';
      $ret['終了日通算'] = 196;
      $ret['終了日確認'] = '07/16';
      $ret['二十四節気'] = '小暑';
      $ret['候']         = '次候';
      $ret['七十二候']     = '蓮始開';
      $ret['七十二候開き'] = '蓮始開';
      $ret['七十二候読み'] = 'はすはじめてひらく';
      $ret['七十二候意味'] = '蓮の花が開き始める';
      break;

    case 197:
    case 198:
    case 199:
    case 200:
    case 201:
    case 202:
      $ret['開始日通算'] = 197;
      $ret['開始日確認'] = '07/17';
      $ret['終了日通算'] = 202;
      $ret['終了日確認'] = '07/22';
      $ret['二十四節気'] = '小暑';
      $ret['候']         = '末候';
      $ret['七十二候']     = '鷹乃学習';
      $ret['七十二候開き'] = '鷹乃学習';
      $ret['七十二候読み'] = 'たかすなわちたくしゅうす';
      $ret['七十二候意味'] = '鷹の幼鳥が飛ぶことを覚える';
      break;

    case 203:
    case 204:
    case 205:
    case 206:
    case 207:
    case 208:
      $ret['開始日通算'] = 203;
      $ret['開始日確認'] = '07/23';
      $ret['終了日通算'] = 208;
      $ret['終了日確認'] = '07/28';
      $ret['二十四節気'] = '大暑';
      $ret['候']         = '初候';
      $ret['七十二候']     = '桐始結花';
      $ret['七十二候開き'] = '桐始結花';
      $ret['七十二候読み'] = 'きりはじめてはなをむすぶ';
      $ret['七十二候意味'] = '桐の実がなり始める';
      break;

    case 209:
    case 210:
    case 211:
    case 212:
    case 213:
      $ret['開始日通算'] = 209;
      $ret['開始日確認'] = '07/29';
      $ret['終了日通算'] = 213;
      $ret['終了日確認'] = '08/02';
      $ret['二十四節気'] = '大暑';
      $ret['候']         = '次候';
      $ret['七十二候']     = '土潤溽暑';
      $ret['七十二候開き'] = '土潤溽暑';
      $ret['七十二候読み'] = 'つちうるおうてむしあつし';
      $ret['七十二候意味'] = '土がしめって蒸し暑くなる';
      break;

    case 214:
    case 215:
    case 216:
    case 217:
      $ret['開始日通算'] = 214;
      $ret['開始日確認'] = '08/03';
      $ret['終了日通算'] = 217;
      $ret['終了日確認'] = '08/06';
      $ret['二十四節気'] = '大暑';
      $ret['候']         = '末候';
      $ret['七十二候']     = '大雨時行';
      $ret['七十二候開き'] = '大雨時行';
      $ret['七十二候読み'] = 'たいうときどきふる';
      $ret['七十二候意味'] = '時として大雨が降る';
      break;

    case 218:
    case 219:
    case 220:
    case 221:
    case 222:
    case 223:
      $ret['開始日通算'] = 218;
      $ret['開始日確認'] = '08/07';
      $ret['終了日通算'] = 223;
      $ret['終了日確認'] = '08/12';
      $ret['二十四節気'] = '立秋';
      $ret['候']         = '初候';
      $ret['七十二候']     = '涼風至';
      $ret['七十二候開き'] = '涼風至';
      $ret['七十二候読み'] = 'すずかぜいたる';
      $ret['七十二候意味'] = '涼しい風が立ち始める';
      break;

    case 224:
    case 225:
    case 226:
    case 227:
    case 228:
      $ret['開始日通算'] = 224;
      $ret['開始日確認'] = '08/13';
      $ret['終了日通算'] = 228;
      $ret['終了日確認'] = '08/17';
      $ret['二十四節気'] = '立秋';
      $ret['候']         = '次候';
      $ret['七十二候']     = '寒蝉鳴';
      $ret['七十二候開き'] = '寒蝉鳴';
      $ret['七十二候読み'] = 'ひぐらしなく';
      $ret['七十二候意味'] = 'ひぐらしが鳴き始める';
      break;

    case 229:
    case 230:
    case 231:
    case 232:
    case 233:
      $ret['開始日通算'] = 229;
      $ret['開始日確認'] = '08/18';
      $ret['終了日通算'] = 233;
      $ret['終了日確認'] = '08/22';
      $ret['二十四節気'] = '立秋';
      $ret['候']         = '末候';
      $ret['七十二候']     = '蒙霧升降';
      $ret['七十二候開き'] = '蒙霧升降';
      $ret['七十二候読み'] = 'ふかききりまとう';
      $ret['七十二候意味'] = '深い霧が立ち込める';
      break;

    case 234:
    case 235:
    case 236:
    case 237:
    case 238:
      $ret['開始日通算'] = 234;
      $ret['開始日確認'] = '08/23';
      $ret['終了日通算'] = 238;
      $ret['終了日確認'] = '08/27';
      $ret['二十四節気'] = '処暑';
      $ret['候']         = '初候';
      $ret['七十二候']     = '綿柎開';
      $ret['七十二候開き'] = '綿柎開';
      $ret['七十二候読み'] = 'わたのはなしべひらく';
      $ret['七十二候意味'] = '綿を包む咢[がく]が開く';
      break;

    case 239:
    case 240:
    case 241:
    case 242:
    case 243:
      $ret['開始日通算'] = 239;
      $ret['開始日確認'] = '08/28';
      $ret['終了日通算'] = 243;
      $ret['終了日確認'] = '09/01';
      $ret['二十四節気'] = '処暑';
      $ret['候']         = '次候';
      $ret['七十二候']     = '天地始粛';
      $ret['七十二候開き'] = '天地始粛';
      $ret['七十二候読み'] = 'てんちはじめてさむし';
      $ret['七十二候意味'] = 'ようやく暑さが鎮まる';
      break;

    case 244:
    case 245:
    case 246:
    case 247:
    case 248:
    case 249:
      $ret['開始日通算'] = 244;
      $ret['開始日確認'] = '09/02';
      $ret['終了日通算'] = 249;
      $ret['終了日確認'] = '09/07';
      $ret['二十四節気'] = '処暑';
      $ret['候']         = '末候';
      $ret['七十二候']     = '禾乃登';
      $ret['七十二候開き'] = '禾乃登';
      $ret['七十二候読み'] = 'こくものすなわちみのる';
      $ret['七十二候意味'] = '稲が実る';
      break;

    case 250:
    case 251:
    case 252:
    case 253:
    case 254:
      $ret['開始日通算'] = 250;
      $ret['開始日確認'] = '09/08';
      $ret['終了日通算'] = 254;
      $ret['終了日確認'] = '09/12';
      $ret['二十四節気'] = '白露';
      $ret['候']         = '初候';
      $ret['七十二候']     = '草露白';
      $ret['七十二候開き'] = '草露白';
      $ret['七十二候読み'] = 'くさのつゆしろし';
      $ret['七十二候意味'] = '草に降りた露が白く光る';
      break;

    case 255:
    case 256:
    case 257:
    case 258:
    case 259:
      $ret['開始日通算'] = 255;
      $ret['開始日確認'] = '09/13';
      $ret['終了日通算'] = 259;
      $ret['終了日確認'] = '09/17';
      $ret['二十四節気'] = '白露';
      $ret['候']         = '次候';
      $ret['七十二候']     = '鶺鴒鳴';
      $ret['七十二候開き'] = '鶺鴒鳴';
      $ret['七十二候読み'] = 'せきれいなく';
      $ret['七十二候意味'] = 'せきれいが鳴き始める';
      break;

    case 260:
    case 261:
    case 262:
    case 263:
    case 264:
      $ret['開始日通算'] = 260;
      $ret['開始日確認'] = '09/18';
      $ret['終了日通算'] = 264;
      $ret['終了日確認'] = '09/22';
      $ret['二十四節気'] = '白露';
      $ret['候']         = '末候';
      $ret['七十二候']     = '玄鳥去';
      $ret['七十二候開き'] = '玄鳥去';
      $ret['七十二候読み'] = 'つばめさる';
      $ret['七十二候意味'] = 'つばめが南へ帰っていく';
      break;

    case 265:
    case 266:
    case 267:
    case 268:
    case 269:
      $ret['開始日通算'] = 265;
      $ret['開始日確認'] = '09/23';
      $ret['終了日通算'] = 269;
      $ret['終了日確認'] = '09/27';
      $ret['二十四節気'] = '秋分';
      $ret['候']         = '初候';
      $ret['七十二候']     = '雷乃収声';
      $ret['七十二候開き'] = '雷乃収声';
      $ret['七十二候読み'] = 'かみなりすなわちこえをおさむ';
      $ret['七十二候意味'] = '雷が鳴り響かなくなる';
      break;

    case 270:
    case 271:
    case 272:
    case 273:
    case 274:
      $ret['開始日通算'] = 270;
      $ret['開始日確認'] = '09/28';
      $ret['終了日通算'] = 274;
      $ret['終了日確認'] = '10/02';
      $ret['二十四節気'] = '秋分';
      $ret['候']         = '次候';
      $ret['七十二候']     = '蟄虫坏戸';
      $ret['七十二候開き'] = '蟄虫[土不/一]戸';
      $ret['七十二候読み'] = 'むしかくれてとをふさぐ';
      $ret['七十二候意味'] = '虫が土中に掘った穴をふさぐ';
      break;

    case 275:
    case 276:
    case 277:
    case 278:
    case 279:
      $ret['開始日通算'] = 275;
      $ret['開始日確認'] = '10/03';
      $ret['終了日通算'] = 279;
      $ret['終了日確認'] = '10/07';
      $ret['二十四節気'] = '秋分';
      $ret['候']         = '末候';
      $ret['七十二候']     = '水始涸';
      $ret['七十二候開き'] = '水始涸';
      $ret['七十二候読み'] = 'みずはじめてかるる';
      $ret['七十二候意味'] = '水が凍り始める';
      break;

    case 280:
    case 281:
    case 282:
    case 283:
    case 284:
      $ret['開始日通算'] = 280;
      $ret['開始日確認'] = '10/08';
      $ret['終了日通算'] = 284;
      $ret['終了日確認'] = '10/12';
      $ret['二十四節気'] = '寒露';
      $ret['候']         = '初候';
      $ret['七十二候']     = '鴻雁来';
      $ret['七十二候開き'] = '鴻雁来';
      $ret['七十二候読み'] = 'こうがんきたる';
      $ret['七十二候意味'] = '雁が飛来し始める';
      break;

    case 285:
    case 286:
    case 287:
    case 288:
    case 289:
      $ret['開始日通算'] = 285;
      $ret['開始日確認'] = '10/13';
      $ret['終了日通算'] = 289;
      $ret['終了日確認'] = '10/17';
      $ret['二十四節気'] = '寒露';
      $ret['候']         = '次候';
      $ret['七十二候']     = '菊花開';
      $ret['七十二候開き'] = '菊花開';
      $ret['七十二候読み'] = 'きくのはなひらく';
      $ret['七十二候意味'] = '菊の花が咲く';
      break;

    case 290:
    case 291:
    case 292:
    case 293:
    case 294:
      $ret['開始日通算'] = 290;
      $ret['開始日確認'] = '10/18';
      $ret['終了日通算'] = 294;
      $ret['終了日確認'] = '10/22';
      $ret['二十四節気'] = '寒露';
      $ret['候']         = '末候';
      $ret['七十二候']     = '蟋蟀在戸';
      $ret['七十二候開き'] = '蟋蟀在戸';
      $ret['七十二候読み'] = 'きりぎりすとにあり';
      $ret['七十二候意味'] = 'きりぎりすが戸にあって鳴く';
      break;

    case 295:
    case 296:
    case 297:
    case 298:
    case 299:
      $ret['開始日通算'] = 295;
      $ret['開始日確認'] = '10/23';
      $ret['終了日通算'] = 299;
      $ret['終了日確認'] = '10/27';
      $ret['二十四節気'] = '霜降';
      $ret['候']         = '初候';
      $ret['七十二候']     = '霜始降';
      $ret['七十二候開き'] = '霜始降';
      $ret['七十二候読み'] = 'しもはじめてふる';
      $ret['七十二候意味'] = '霜が降り始める';
      break;

    case 300:
    case 301:
    case 302:
    case 303:
    case 304:
      $ret['開始日通算'] = 300;
      $ret['開始日確認'] = '10/28';
      $ret['終了日通算'] = 304;
      $ret['終了日確認'] = '11/01';
      $ret['二十四節気'] = '霜降';
      $ret['候']         = '次候';
      $ret['七十二候']     = '霎時施';
      $ret['七十二候開き'] = '霎時施';
      $ret['七十二候読み'] = 'こさめときどきふる';
      $ret['七十二候意味'] = '小雨がしとしと降る';
      break;

    case 305:
    case 306:
    case 307:
    case 308:
    case 309:
      $ret['開始日通算'] = 305;
      $ret['開始日確認'] = '11/02';
      $ret['終了日通算'] = 309;
      $ret['終了日確認'] = '11/06';
      $ret['二十四節気'] = '霜降';
      $ret['候']         = '末候';
      $ret['七十二候']     = '楓蔦黄';
      $ret['七十二候開き'] = '楓蔦黄';
      $ret['七十二候読み'] = 'もみじつたきばむ';
      $ret['七十二候意味'] = 'もみじや蔦が黄葉する';
      break;

    case 310:
    case 311:
    case 312:
    case 313:
    case 314:
      $ret['開始日通算'] = 310;
      $ret['開始日確認'] = '11/07';
      $ret['終了日通算'] = 314;
      $ret['終了日確認'] = '11/11';
      $ret['二十四節気'] = '立冬';
      $ret['候']         = '初候';
      $ret['七十二候']     = '山茶始開';
      $ret['七十二候開き'] = '山茶始開';
      $ret['七十二候読み'] = 'つばきはじめてひらく';
      $ret['七十二候意味'] = 'つばきの花が咲き始める';
      break;

    case 315:
    case 316:
    case 317:
    case 318:
    case 319:
      $ret['開始日通算'] = 315;
      $ret['開始日確認'] = '11/12';
      $ret['終了日通算'] = 319;
      $ret['終了日確認'] = '11/16';
      $ret['二十四節気'] = '立冬';
      $ret['候']         = '次候';
      $ret['七十二候']     = '地始凍';
      $ret['七十二候開き'] = '地始凍';
      $ret['七十二候読み'] = 'ちはじめてこおる';
      $ret['七十二候意味'] = '大地が凍り始める';
      break;

    case 320:
    case 321:
    case 322:
    case 323:
    case 324:
      $ret['開始日通算'] = 320;
      $ret['開始日確認'] = '11/17';
      $ret['終了日通算'] = 324;
      $ret['終了日確認'] = '11/21';
      $ret['二十四節気'] = '立冬';
      $ret['候']         = '末候';
      $ret['七十二候']     = '金盞香';
      $ret['七十二候開き'] = '金盞香';
      $ret['七十二候読み'] = 'きんせんかさく';
      $ret['七十二候意味'] = '水仙の花が咲く';
      break;

    case 325:
    case 326:
    case 327:
    case 328:
    case 329:
      $ret['開始日通算'] = 325;
      $ret['開始日確認'] = '11/22';
      $ret['終了日通算'] = 329;
      $ret['終了日確認'] = '11/26';
      $ret['二十四節気'] = '小雪';
      $ret['候']         = '初候';
      $ret['七十二候']     = '虹蔵不見';
      $ret['七十二候開き'] = '虹蔵不見';
      $ret['七十二候読み'] = 'にじかくいれてみえず';
      $ret['七十二候意味'] = '虹を見かけなくなる';
      break;

    case 330:
    case 331:
    case 332:
    case 333:
    case 334:
      $ret['開始日通算'] = 330;
      $ret['開始日確認'] = '11/27';
      $ret['終了日通算'] = 334;
      $ret['終了日確認'] = '12/01';
      $ret['二十四節気'] = '小雪';
      $ret['候']         = '次候';
      $ret['七十二候']     = '朔風払葉';
      $ret['七十二候開き'] = '朔風払葉';
      $ret['七十二候読み'] = 'きたかぜこのはをはらう';
      $ret['七十二候意味'] = '北風が木の葉を払いのける';
      break;

    case 335:
    case 336:
    case 337:
    case 338:
    case 339:
      $ret['開始日通算'] = 335;
      $ret['開始日確認'] = '12/02';
      $ret['終了日通算'] = 339;
      $ret['終了日確認'] = '12/06';
      $ret['二十四節気'] = '小雪';
      $ret['候']         = '末候';
      $ret['七十二候']     = '橘始黄';
      $ret['七十二候開き'] = '橘始黄';
      $ret['七十二候読み'] = 'たちばなはじめてきばむ';
      $ret['七十二候意味'] = '橘の葉が黄葉し始める';
      break;

    case 340:
    case 341:
    case 342:
    case 343:
    case 344:
      $ret['開始日通算'] = 340;
      $ret['開始日確認'] = '12/07';
      $ret['終了日通算'] = 344;
      $ret['終了日確認'] = '12/11';
      $ret['二十四節気'] = '大雪';
      $ret['候']         = '初候';
      $ret['七十二候']     = '閉塞成冬';
      $ret['七十二候開き'] = '閉塞成冬';
      $ret['七十二候読み'] = 'そらさむくふゆとなる';
      $ret['七十二候意味'] = '天地の気が塞がって冬となる';
      break;

    case 345:
    case 346:
    case 347:
    case 348:
      $ret['開始日通算'] = 345;
      $ret['開始日確認'] = '12/12';
      $ret['終了日通算'] = 348;
      $ret['終了日確認'] = '12/15';
      $ret['二十四節気'] = '大雪';
      $ret['候']         = '次候';
      $ret['七十二候']     = '熊蟄穴';
      $ret['七十二候開き'] = '熊蟄穴';
      $ret['七十二候読み'] = 'くまあなにこもる';
      $ret['七十二候意味'] = '熊が冬眠のために穴に隠れる';
      break;

    case 349:
    case 350:
    case 351:
    case 352:
    case 353:
    case 354:
      $ret['開始日通算'] = 349;
      $ret['開始日確認'] = '12/16';
      $ret['終了日通算'] = 354;
      $ret['終了日確認'] = '12/21';
      $ret['二十四節気'] = '大雪';
      $ret['候']         = '末候';
      $ret['七十二候']     = '?魚群';
      $ret['七十二候開き'] = '[魚厥]魚群';
      $ret['七十二候読み'] = 'さけのうおむらがる';
      $ret['七十二候意味'] = '鮭が群がり川を上る';
      break;

    case 355:
    case 356:
    case 357:
    case 358:
    case 359:
      $ret['開始日通算'] = 355;
      $ret['開始日確認'] = '12/22';
      $ret['終了日通算'] = 359;
      $ret['終了日確認'] = '12/26';
      $ret['二十四節気'] = '冬至';
      $ret['候']         = '初候';
      $ret['七十二候']     = '乃東生';
      $ret['七十二候開き'] = '乃東生';
      $ret['七十二候読み'] = 'なつかれくさしょうず';
      $ret['七十二候意味'] = '夏枯草が芽を出す';
      break;

    case 360:
    case 361:
    case 362:
    case 363:
    case 364:
      $ret['開始日通算'] = 360;
      $ret['開始日確認'] = '12/27';
      $ret['終了日通算'] = 364;
      $ret['終了日確認'] = '12/31';
      $ret['二十四節気'] = '冬至';
      $ret['候']         = '次候';
      $ret['七十二候']     = '麋角解';
      $ret['七十二候開き'] = '麋角解';
      $ret['七十二候読み'] = 'さわしかつのおる';
      $ret['七十二候意味'] = '大鹿が角を落とす';
      break;

    case 0:
    case 1:
    case 2:
    case 3:
      $ret['開始日通算'] = 0;
      $ret['開始日確認'] = '01/01';
      $ret['終了日通算'] = 3;
      $ret['終了日確認'] = '01/04';
      $ret['二十四節気'] = '冬至';
      $ret['候']         = '末候';
      $ret['七十二候']     = '雪下出麦';
      $ret['七十二候開き'] = '雪下出麦';
      $ret['七十二候読み'] = 'ゆきわたりてむぎのびる';
      $ret['七十二候意味'] = '雪の下で麦が芽を出す';
      break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      $ret['開始日通算'] = 4;
      $ret['開始日確認'] = '01/05';
      $ret['終了日通算'] = 8;
      $ret['終了日確認'] = '01/09';
      $ret['二十四節気'] = '小寒';
      $ret['候']         = '初候';
      $ret['七十二候']     = '芹乃栄';
      $ret['七十二候開き'] = '芹乃栄';
      $ret['七十二候読み'] = 'せりすなわちさかう';
      $ret['七十二候意味'] = '芹がよく生育する';
      break;

    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
      $ret['開始日通算'] = 9;
      $ret['開始日確認'] = '01/10';
      $ret['終了日通算'] = 13;
      $ret['終了日確認'] = '01/14';
      $ret['二十四節気'] = '小寒';
      $ret['候']         = '次候';
      $ret['七十二候']     = '水泉動';
      $ret['七十二候開き'] = '水泉動';
      $ret['七十二候読み'] = 'しみずあたたかをふくむ';
      $ret['七十二候意味'] = '地中で凍った泉が動き始める';
      break;

    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
      $ret['開始日通算'] = 14;
      $ret['開始日確認'] = '01/15';
      $ret['終了日通算'] = 18;
      $ret['終了日確認'] = '01/19';
      $ret['二十四節気'] = '小寒';
      $ret['候']         = '末候';
      $ret['七十二候']     = '雉始?';
      $ret['七十二候開き'] = '雉始[句隹]';
      $ret['七十二候読み'] = 'きじはじめてなく';
      $ret['七十二候意味'] = '雄の雉が鳴き始める';
      break;

    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
      $ret['開始日通算'] = 19;
      $ret['開始日確認'] = '01/20';
      $ret['終了日通算'] = 23;
      $ret['終了日確認'] = '01/24';
      $ret['二十四節気'] = '大寒';
      $ret['候']         = '初候';
      $ret['七十二候']     = '款冬華';
      $ret['七十二候開き'] = '款冬華';
      $ret['七十二候読み'] = 'ふきのはなさく';
      $ret['七十二候意味'] = 'ふきのとうがつぼみを出す';
      break;

    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
      $ret['開始日通算'] = 24;
      $ret['開始日確認'] = '01/25';
      $ret['終了日通算'] = 28;
      $ret['終了日確認'] = '01/29';
      $ret['二十四節気'] = '大寒';
      $ret['候']         = '次候';
      $ret['七十二候']     = '水沢腹堅';
      $ret['七十二候開き'] = '水沢腹堅';
      $ret['七十二候読み'] = 'さわみずこおりつめる';
      $ret['七十二候意味'] = '沢に氷が厚く張りつめる';
      break;

    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
      $ret['開始日通算'] = 29;
      $ret['開始日確認'] = '01/30';
      $ret['終了日通算'] = 33;
      $ret['終了日確認'] = '02/03';
      $ret['二十四節気'] = '大寒';
      $ret['候']         = '末候';
      $ret['七十二候']     = '鶏始乳';
      $ret['七十二候開き'] = '[奚隹]始乳';
      $ret['七十二候読み'] = 'にわとりはじめてとやにつく';
      $ret['七十二候意味'] = '鶏が卵を産み始める';
      break;

  }
  //
  return $ret;
}


//private:
private $時鐘_;
private $辰刻_;
private $開始日通算_;
private $開始日確認_;
private $終了日通算_;
private $終了日確認_;
private $二十四節気_;
private $候_;
private $七十二候_;
private $七十二候開き_;
private $七十二候読み_;
private $七十二候意味_;
} // end of class

