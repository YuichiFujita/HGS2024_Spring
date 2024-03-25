//============================================================
//
//	データ保存マネージャーヘッダー [retentionManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	クラス定義
//************************************************************
// データ保存マネージャークラス
class CRetentionManager
{
public:
	// 勝利列挙
	enum EWin
	{
		WIN_NONE,	// 無し
		WIN_FAILED,	// 勝利失敗
		WIN_CLEAR,	// 勝利成功
		WIN_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CRetentionManager();

	// デストラクタ
	~CRetentionManager();

	// リザルト情報構造体
	struct SResult
	{
		long nScore;	// 経過タイム
		long nTime;	// 経過タイム
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了

	// 静的メンバ関数
	static CRetentionManager *Create(void);	// 生成
	static void Release(CRetentionManager *&prRetentionManager);	// 破棄

	// メンバ関数
	void SetScore(const long Score);	// リザルト情報設定
	int GetScore(void) const { return m_Score.nScore; }	// リザルト情報取得
	void SetResult(const long nTime);	// リザルト情報設定
	int GetResult(void) const { return m_result.nTime; }	// リザルト情報取得

private:
	// メンバ変数
	SResult m_result;	// リザルト情報
	SResult m_Score;	// リザルト情報
};

#endif	// _RETENTION_MANAGER_H_
