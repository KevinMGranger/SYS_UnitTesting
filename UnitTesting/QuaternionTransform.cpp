#include "QuaternionTransform.h"

ostream& operator<<(ostream& os, QuaternionTransform const& at)
{
	return os <<
		"P(" <<
		at.pos.x << ", " << at.pos.y << ", " << at.pos.z << ") " <<
		"S(" <<
		at.scale.x << ", " << at.scale.y << ", " << at.scale.z << ") " <<
		"Q(" <<
		at.quat.x << ", " << at.quat.y << ", " << at.quat.z << ", " << at.quat.w << ") " <<
		'\n';
}

void make_worldmatrix(QuaternionTransform const& qt, XMFLOAT4X4 &mat)
{
	XMVECTOR trans_vec = XMLoadFloat3(&qt.pos);
	XMMATRIX trans_mat = XMMatrixTranslationFromVector(trans_vec);

	XMVECTOR scale_vec = XMLoadFloat3(&qt.scale);
	XMMATRIX scale_mat = XMMatrixScalingFromVector(scale_vec);

	XMVECTOR rotat_vec = XMLoadFloat4(&qt.quat);
	XMMATRIX rotat_mat = XMMatrixRotationQuaternion(rotat_vec);

	XMMATRIX world = scale_mat * rotat_mat * trans_mat;

	XMStoreFloat4x4(&mat, world);
}

XMFLOAT4X4 make_worldmatrix(QuaternionTransform const& qt)
{
	XMFLOAT4X4 mat;
	make_worldmatrix(qt, mat);

	return mat;
}