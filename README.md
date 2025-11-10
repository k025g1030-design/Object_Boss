# Object_Boss

- [ゲームについて](#ゲームについて)
  - [ゲーム説明](#ゲーム説明) 
  - [素材](#素材)
  - [素材処理](#素材処理)
- [ストーリー](#ストーリー)
- [まとめ](#まとめ)
- [作者](#作者)

## ゲームについて
### ゲーム説明

### 素材
#### 画像


#### 音
##### 音_1



### 素材処理
#### 画像編集ソフト
##### 時限爆弾


## プログラムについて
### 開発環境
 - Visual Studio 2022

### 環境変数

#### 環境変数
![環境変数](./Doc/Images/EnvEdit_01.png)

他の方法：
 1. **Windowsキー** を押し、「環境変数」と入力 → **「システム環境変数の編集」** をクリック。
 2. 「システムのプロパティ」ウィンドウが開くので、下部の **「環境変数(N)...」** ボタンをクリック。

#### 環境変数 ``KAMATA_ENGINE`` を設定
![環境変数](./Doc/Images/EnvEdit_02.png)

![環境変数](./Doc/Images/EnvEdit_03.png)
 
  - **KAMATA_ENGINE** : ``<KamataEngineのパス>``
 - **<KamataEngineのパス>** : ``C:\path\to\KamataEngine`` のように、**KamataEngine** フォルダの絶対パスを指定。

#### テストする
**PowerShell**の方は：
```powershell
echo $env:KAMATA_ENGINE
```
**コマンドプロンプト**の方は：
```cmd
echo %KAMATA_ENGINE%
```
パスが表示されれば成功です。
### コンパイラの「インクルードパス」を設定
``include/`` 配下のヘッダーファイルを直接見つけられるようにする：

 1. プロジェクトを右クリック → ``Properties``（プロパティ）。
 2. 左ペインで ``Configuration Properties → C/C++ → General`` を選択。
 3. Additional Include Directories に次を追加：
```
$(ProjectDir)include;
```

``$(ProjectDir)`` マクロを使うと、絶対パスのハードコードを避けられます。階層が深い場合は ``$(SolutionDir)libs\engine\include`` などに変更してください。
左上の **Configuration** は **「All Configurations」、Platform** は **「All Platforms」** を選択すると、**Debug/Release、Win32/x64** の両方に適用されます。

## ストーリー


## まとめ：


## 作者
日本工学院専門学校
[]()
[]()
[]()
[]()
