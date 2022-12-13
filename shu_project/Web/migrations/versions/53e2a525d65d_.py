"""empty message

Revision ID: 53e2a525d65d
Revises: 41fc5b47ddd8
Create Date: 2022-12-12 14:02:12.529037

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = '53e2a525d65d'
down_revision = '41fc5b47ddd8'
branch_labels = None
depends_on = None


def upgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.add_column('user', sa.Column('name', sa.String(length=8), nullable=False))
    op.add_column('user', sa.Column('location', sa.String(length=256), nullable=True))
    op.add_column('user', sa.Column('about_me', sa.String(length=256), nullable=True))
    op.create_unique_constraint(None, 'user', ['name'])
    # ### end Alembic commands ###


def downgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_constraint(None, 'user', type_='unique')
    op.drop_column('user', 'about_me')
    op.drop_column('user', 'location')
    op.drop_column('user', 'name')
    # ### end Alembic commands ###