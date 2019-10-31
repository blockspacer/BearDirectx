#pragma once
class DX12RenderViewport :public BearRenderBase::BearRenderViewportBase
{
public:
	BEAR_CLASS_NO_COPY(DX12RenderViewport);
	DX12RenderViewport(void * Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync, const BearGraphics::BearRenderViewportDescription&Description);
	virtual ~DX12RenderViewport();
	virtual void SetVSync(bool Sync);
	virtual void SetFullScreen(bool FullScreen);
	virtual void Resize(bsize Width, bsize Height);
	virtual void*GetHandle();

	void Flush(bool wait);
	void Wait();
	
	BearGraphics::BearRenderViewportDescription Description;
	ComPtr<ID3D12GraphicsCommandList> CommandList;
private:
	void ReInit(bsize Width, bsize Height);
	ComPtr<ID3D12CommandQueue> CommandQueue;

	ComPtr<ID3D12CommandAllocator> CommandAllocator;

	ComPtr<IDXGISwapChain3> SwapChain;
	ComPtr<ID3D12DescriptorHeap> RtvHeap;

	constexpr static bsize FrameCount = 2;
	UINT FrameIndex;
	ComPtr<ID3D12Resource> RenderTargets[FrameCount];

	CD3DX12_CPU_DESCRIPTOR_HANDLE RtvHandle;

	HANDLE FenceEvent;
	ComPtr<ID3D12Fence> Fence;
	UINT64 FenceValue;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	bool m_Fullscreen;
	bool m_VSync;
	bsize m_Width;
	bsize m_Height;
	bool m_wait;
	int8 m_Status;
};