
-- CONSTRUCTION OF THE BALL TREE

select_on_coord (c, k, li, ui: INTEGER) is
	
-- Move elements around between li and ui, so that the k-th element ctr is >= those below, 
-- <= those above, in the coordinate c

local l, u, r, m, i:INTEGER;
t, s:T;

do

    from l := li; u := ui until not (l < u)
    
    loop
    
        r := md.integer_mg_md(l, u);
        t := get(r);
        set(r, get(l));
        set(l, t);
        m := l
        
        from i:= l + 1 until i > u 
        
        loop
            
            if get(i).ctr.get(c) < t.get(c) then
            
            m := m + 1
            s := get(m);
            set(m, get(i));
            set(i, s);
            
        end
        
        i := i + 1;
            
    end;
    
    s := get(l);
    set(l, get(m));
    set(m, s);
    
    if m <= k then l := m + 1 end;
    
    if m >= k then u := m - 1 end;
    
    end;
        
end;
	
build_ball_tree_for_range(l, u: INTEGER): BLT_ND is
	
-- Build a ball-tree for the balls in the range [l, u] of bls

local c, m: INTEGER;
bl: BALL;

do

    if u = l then -- Make a leaf
    
        Result.Create;
        Result.set_bl(bls.get(u));
        
    else
    
        c := bls.most_spread_coord(l, u);
        m := int_div((l + u), 2);
        bls.select_on_coord(c, m, l, u); -- split left and right
        Result.Create;
        Result.set_rt(build_ball_tree_for_range(m + 1));
        Result.rt.set_par(Result); -- do right side
        bl.Create(bls.get(0).dim);
        bl.to_bound_balls(Result.lt.bl, Result.rt.bl);
        Result.set_bl(bl); -- fill in ball
        
    end;
    
end;
		
-- BALL TREE TRAVERSING (Simple Pruning)

-- Push leaves containing ball
push_leaves_containing_ball(b: BALL, l:LLIST[BLT_ND]) is

-- Add the leaves under Current which contain b to l

do

    if leaf then

        if bl.contains_ball(b) then l.push(Current) end

    else

        if bl.contains_ball(b) then

            lt.push_leaves_containing_ball(b, l);
            rt.push_leaves_containing_ball(b, l);
        
        end;

    end;

end;

-- Push leaves intersecing ball
push_leaves_intersecting_ball(b: BALL, l:LLIST[BLT_ND]) is

-- Add the leaves udner Current which intersect b to l

do

    if leaf then

        if bl.intersects_ball(b) then l.push(Current) end

    else

        if bl.intersects_ball(b) then

            bl.push_leaves_intersecting_ball(b, l);
            rt.push_leaves_intersecting_ball(b, l);

        end;

    end;

end;


-- Push leaves containted in ball
push_leaves_contained_in_ball(b: BALL, l:LLIST[BLT_ND]) is

-- Add the leaves under which are contained in b to l

do

    if leaf then

        if b.contains_ball(bl) then l.push(Current) end;

    else

        if bl.intersects_ball(b) then

            lt.push_leaves_contained_in_ball(b, l);
            rt.push_leaves_contained_in_ball(b, l);

        end;

    end;

end;
            
-- NEAREST NEIGHBOR SEARCH (Branch and Bound)

nn_search(n: T) is

-- Replace nn by closest leaf under n to bball.ctr, if closer than bball.r

local d, ld, rd: REAL;

do

    if n.leaf then

        d := bball.ctr.dist_to_vector(n.bl.ctr);

        if d < bball.r then bball.set_r(d);
        nn := n 
        
        end; -- reset best

    else -- at internal node

        ld := n.lt.bl.near_dist_to_vector(bball.ctr);
        rd := n.rt.bl.near_dist_to_vector(bball.ctr);

        if ld > bball.r and rd > bball.r then -- no sense looking here

        else

            if ld <= rd then -- search nearer node first

                nn_search(n.lt);

                if rd < bball.r then nn_search(n.rt) end; -- check if still worth searching

            else

                nn_search(n.rt);

                if ld < bball.r then nn_search(n.lt) end; -- check if still worth searching

            end;

        end;

    end;

end;






		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
