// Generated from /Users/sadegh/Desktop/Personal/Programming Languages and Compilers/project/src/Smoola.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.AbstractParseTreeVisitor;

/**
 * This class provides an empty implementation of {@link SmoolaVisitor},
 * which can be extended to create a visitor which only needs to handle a subset
 * of the available methods.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public class SmoolaBaseVisitor<T> extends AbstractParseTreeVisitor<T> implements SmoolaVisitor<T> {
	/**
	 * {@inheritDoc}
	 *
	 * <p>The default implementation returns the result of calling
	 * {@link #visitChildren} on {@code ctx}.</p>
	 */
	@Override public T visitProg(SmoolaParser.ProgContext ctx) { return visitChildren(ctx); }
	/**
	 * {@inheritDoc}
	 *
	 * <p>The default implementation returns the result of calling
	 * {@link #visitChildren} on {@code ctx}.</p>
	 */
	@Override public T visitExpr(SmoolaParser.ExprContext ctx) { return visitChildren(ctx); }
}