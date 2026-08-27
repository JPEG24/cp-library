# cp-library
[![Actions Status](https://github.com/JPEG24/cp-library/actions/workflows/verify.yaml/badge.svg)](https://github.com/JPEG24/cp-library/actions)
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://JPEG24.github.io/cp-library)

競技プログラミング用のC++ライブラリです。

## 環境
- C++ 17
- ac-library

## 内容
- `atcoder`
AtCoder Library

- `tools`
  - `rtest`
	問題を解く`main.cpp`の直下にこのディレクトリを配置し、ランダムテストを行う。

	  - `gen.cpp`
		入力を生成するコードを書く。

	  - `naive.cpp`
		生成される入力に対して正しい出力を返すコードを書く。実際に問題の制約で解く必要はない。

	  - `test.sh`
		実行するとランダムテストを開始する。

  - `inter`
	問題を解く`main.cpp`の直下にこのディレクトリを配置し、インタラクティブな問題のランダムテストを行う。

	  - `judge.cpp`
		ジャッジとして動作するコードを書く。

	  - `test.sh`
		実行するとランダムテストを開始する。