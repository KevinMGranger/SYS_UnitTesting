#include "AxisTransform.h"

ostream& operator<<(ostream& os, AxisTransform const& at)
{
	return os <<
		"P(" <<
		at.pos.x << ", " << at.pos.y << ", " << at.pos.z << ") " <<
		"S(" <<
		at.scale.x << ", " << at.scale.y << ", " << at.scale.z << ") " <<
		"A(" <<
		at.axis.x << ", " << at.axis.y << ", " << at.axis.z << ") " <<
		'\n';
}

void make_worldmatrix(AxisTransform const& at, XMFLOAT4X4 &mat)
{
	XMVECTOR trans_vec = XMLoadFloat3(&at.pos);
	XMMATRIX trans_mat = XMMatrixTranslationFromVector(trans_vec);

	XMVECTOR scale_vec = XMLoadFloat3(&at.scale);
	XMMATRIX scale_mat = XMMatrixScalingFromVector(scale_vec);

	XMVECTOR rotat_vec = XMLoadFloat3(&at.axis);
	float angle = at.rotation_amount;
	XMMATRIX rotat_mat = XMMatrixRotationAxis(rotat_vec, angle);

	XMMATRIX world = scale_mat * rotat_mat * trans_mat;

	XMStoreFloat4x4(&mat, world);
}

XMFLOAT4X4 make_worldmatrix(AxisTransform const& at)
{
	XMFLOAT4X4 mat;
	make_worldmatrix(at, mat);

	return mat;
}