enum class PieceType
{
	King = 1,
	Queen,
	Rook = 10,
	Pawn
};

int main()
{
	{
		PieceType piece{ PieceType::King };

		if (piece == PieceType::King)
		{
			/* ... */
		}
	}

	{
        // 使用using enum声明来避免使用枚举值的全名
        // 不然使用King时要使用PieceType::King
		using enum PieceType;
		PieceType piece{ King };
	}

	{
        // 使用using声明避免使用某个特定枚举值的全名
		using PieceType::King;
		PieceType piece{ King };
		piece = PieceType::Queen;
	}
}
