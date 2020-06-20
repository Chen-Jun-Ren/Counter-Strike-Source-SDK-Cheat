class IClientNetworkable
{
public:
	//virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void IClientNetworkable_Whatever_fun_0() = 0;
	virtual void			Release() = 0;
	virtual ClientClass* GetClientClass() = 0;
	virtual void			NotifyShouldTransmit(int state) = 0;
	virtual void			OnPreDataChanged(int updateType) = 0;
	virtual void			OnDataChanged(int updateType) = 0;
	virtual void			PreDataUpdate(int updateType) = 0;
	virtual void			PostDataUpdate(int updateType) = 0;
	virtual bool			IsDormant() = 0;
	virtual int				GetIndex() const = 0;
	virtual void			IClientNetworkable_Whatever_fun_1() = 0;
	virtual void* GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities() = 0;
};