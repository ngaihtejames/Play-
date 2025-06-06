#pragma once

#include <thread>
#include <QMainWindow>
#include "PsfVm.h"
#include "PsfBase.h"
#include "PlaybackController.h"
#include "playlistmodel.h"
#include "filesystem_def.h"

namespace Ui
{
	class MainWindow;
}

#ifdef DEBUGGER_INCLUDED
class DebuggerWindow;

namespace Ui
{
	class DebugMenu;
}
#endif

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

	void AddFileToPlaylist(const fs::path&);
	void AddArchiveToPlaylist(const fs::path&);
	void ShowDebugger();

private:
	void UpdateTrackDetails(CPsfBase::TagMap&);
	void OnNewFrame();

	void UnloadCurrentTrack();
	void PlayTrackIndex(int index);
	void DeleteTrackIndex(int index);

	void SetupDebugger();

	void closeEvent(QCloseEvent*) override;

	Ui::MainWindow* ui;
	CPsfVm* m_virtualMachine;
	PlaylistModel model;
	int m_currentindex = -1;
	CPlaybackController m_playbackController;

	fs::path m_path;

#ifdef DEBUGGER_INCLUDED
	std::unique_ptr<DebuggerWindow> m_debugger;
	Ui::DebugMenu* debugMenuUi = nullptr;
#endif

	Framework::CSignal<void()>::Connection m_OnNewFrameConnection;

	Framework::CSignal<void(float)>::Connection m_PlaybackVolumeChangedConnection;
	Framework::CSignal<void()>::Connection m_PlaybackCompletedConnection;

signals:
	void playbackCompleted();

private slots:
	void on_actionOpen_triggered();
	void on_tableView_doubleClicked(const QModelIndex& index);
	void on_playpauseButton_clicked();
	void on_nextButton_clicked();
	void on_prevButton_clicked();
	void on_tableView_customContextMenuRequested(const QPoint& pos);
	void on_actionPlayPause_triggered();
	void on_actionPrev_triggered();
	void on_actionNext_triggered();
	void on_playbackCompleted();
};
